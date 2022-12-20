#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

struct Blueprint {
    public:
        int oreRobotOreCost;
        int clayRobotOreCost;
        int obsidianRobotOreCost;
        int obsidianRobotClayCost;
        int geodeRobotOreCost;
        int geodeRobotObsidianCost;
    
        Blueprint(int oreOre, int clayOre, int obbyOre, int obbyClay, int geodeOre, int geodeObby) {
            oreRobotOreCost = oreOre;
            clayRobotOreCost = clayOre;
            obsidianRobotOreCost = obbyOre;
            obsidianRobotClayCost = obbyClay;
            geodeRobotOreCost = geodeOre;
            geodeRobotObsidianCost = geodeObby;
        }

        int highestOreCost() {
            return std::max(std::max(oreRobotOreCost, clayRobotOreCost), std::max(obsidianRobotOreCost, geodeRobotOreCost));
        }
};

using namespace std;

int findGeodesInTime(Blueprint& blueprint, int timeLeft = 32, 
    int oreRobots = 1, int clayRobots = 0, int obsidianRobots = 0, int geodeRobots = 0,
    int oreOnHand = 0, int clayOnHand = 0, int obsidianOnHand = 0, int geodesOnHand = 0,
    bool declinedOreRobot = false, bool declinedClayRobot = false, bool declinedObsidianRobot = false, bool declinedGeodeRobot = false
);

int main() {
    string junk; // A lot of junk to parse here
    int oreOre, clayOre, obbyOre, obbyClay, geodeOre, geodeObby ;
    vector<Blueprint> blueprints;

    // Go until end of file
    while (blueprints.size() < 3 && (cin >> junk)) { // Blueprint
        cin >> junk >> junk >> junk >> junk >> junk; // #: Each ore robot costs
        cin >> oreOre;
        cin >> junk >> junk >> junk >> junk >> junk; // ore. Each clay robot costs
        cin >> clayOre;
        cin >> junk >> junk >> junk >> junk >> junk; // ore. Each obsidian robot costs
        cin >> obbyOre;
        cin >> junk >> junk; // ore and
        cin >> obbyClay;
        cin >> junk >> junk >> junk >> junk >> junk; // clay. Each geode robot costs
        cin >> geodeOre;
        cin >> junk >> junk; // ore and
        cin >> geodeObby;
        getline(cin, junk); // obsidan.

        blueprints.push_back(Blueprint(oreOre, clayOre, obbyOre, obbyClay, geodeOre, geodeObby));
    }

    int quality = 1;

    // Just multiply the amount we can find together
    for (int i = 0; i < blueprints.size(); i++) {
        int geodesFound = findGeodesInTime(blueprints[i]);
        quality *= geodesFound;
    }

    cout << quality << endl;

    return 0;
}

// Optimizations:
//    Will not build a previously declined robot until another robot is build
//    Will not build a robot if our current count of that robot is equal to the maximum cost of that resource
//    Will not build a robot if our stock of that resource combined with our robot count achieves the same purpose
int findGeodesInTime(Blueprint& blueprint, int timeLeft, 
    int oreRobots, int clayRobots, int obsidianRobots, int geodeRobots,
    int oreOnHand, int clayOnHand, int obsidianOnHand, int geodesOnHand,
    bool declinedOreRobot, bool declinedClayRobot, bool declinedObsidianRobot, bool declinedGeodeRobot
) {
    if (timeLeft <= 0) {
        return geodesOnHand;
    }
    int geodeYield = 0;
    // See if we could build an ore robot
    if (!declinedOreRobot && oreOnHand >= blueprint.oreRobotOreCost && ((timeLeft * oreRobots) + oreOnHand) < (timeLeft * blueprint.highestOreCost())) {
        // Build an ore robot
        geodeYield = max(geodeYield, findGeodesInTime(blueprint, timeLeft - 1, 
            oreRobots + 1, clayRobots, obsidianRobots, geodeRobots,
            oreOnHand + oreRobots - blueprint.oreRobotOreCost, clayOnHand + clayRobots, obsidianOnHand + obsidianRobots, geodesOnHand + geodeRobots
        ));
        declinedOreRobot = true;
    }

    // See if we could build a clay robot
    if (!declinedClayRobot && oreOnHand >= blueprint.clayRobotOreCost && ((timeLeft * clayRobots) + clayOnHand) < (timeLeft * blueprint.obsidianRobotClayCost)) {
        // Build a clay robot
        geodeYield = max(geodeYield, findGeodesInTime(blueprint, timeLeft - 1, 
            oreRobots, clayRobots + 1, obsidianRobots, geodeRobots,
            oreOnHand + oreRobots - blueprint.clayRobotOreCost, clayOnHand + clayRobots, obsidianOnHand + obsidianRobots, geodesOnHand + geodeRobots
        ));
        declinedClayRobot = true;
    }

    // See if we could build an obsidian robot
    if (!declinedObsidianRobot && oreOnHand >= blueprint.obsidianRobotOreCost && clayOnHand >= blueprint.obsidianRobotClayCost && ((timeLeft * obsidianRobots) + obsidianOnHand) < (timeLeft * blueprint.geodeRobotObsidianCost)) {
        // Build an obsidian robot
        geodeYield = max(geodeYield, findGeodesInTime(blueprint, timeLeft - 1, 
            oreRobots, clayRobots, obsidianRobots + 1, geodeRobots,
            oreOnHand + oreRobots - blueprint.obsidianRobotOreCost, clayOnHand + clayRobots - blueprint.obsidianRobotClayCost, obsidianOnHand + obsidianRobots, geodesOnHand + geodeRobots
        ));
        declinedObsidianRobot = true;
    }

    // See if we could build a geode robot
    if (!declinedGeodeRobot && oreOnHand >= blueprint.geodeRobotOreCost && obsidianOnHand >= blueprint.geodeRobotObsidianCost) {
        // Build a geode robot
        geodeYield = max(geodeYield, findGeodesInTime(blueprint, timeLeft - 1, 
            oreRobots, clayRobots, obsidianRobots, geodeRobots + 1,
            oreOnHand + oreRobots - blueprint.geodeRobotOreCost, clayOnHand + clayRobots, obsidianOnHand + obsidianRobots - blueprint.geodeRobotObsidianCost, geodesOnHand + geodeRobots
        ));
        declinedObsidianRobot = true;
    }

    // Now see what happens if we don't make any robots right now
    geodeYield = max(geodeYield, findGeodesInTime(blueprint, timeLeft - 1, 
        oreRobots, clayRobots, obsidianRobots, geodeRobots,
        oreOnHand + oreRobots, clayOnHand + clayRobots, obsidianOnHand + obsidianRobots, geodesOnHand + geodeRobots,
        declinedOreRobot, declinedClayRobot, declinedObsidianRobot, declinedGeodeRobot
    ));

    return geodeYield;
}