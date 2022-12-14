#ifndef AOC_LIST_OR_INT
#define AOC_LIST_OR_INT

#include <vector>

class ListOrInt {
    private:
        int _intValue;
        std::vector<ListOrInt> _listValue;
        bool _isList;

    public:
        ListOrInt(bool isList) {
            _isList = isList;
        }

        void addItem(ListOrInt& item) {
            if (_isList) {
                _listValue.push_back(item);
            }
        }

        void setIntValue(int value) {
            if (!_isList) {
                _intValue = value;
            }
        }

        int getIntValue() {
            if (!_isList) {
                return _intValue;
            } else {
                return -1;
            }
        }

        std::vector<ListOrInt> getListValue() {
            if (_isList) {
                return _listValue;
            } else {
                return std::vector<ListOrInt>();
            }
        }

        int compareTo(ListOrInt& right) {
            if (!_isList && !right._isList) {
                // Int vs Int
                if (_intValue < right._intValue) {
                    return 1;
                }
                if (_intValue > right._intValue) {
                    return -1;
                } else {
                    return 0;
                }
            }
            ListOrInt* l = this;
            ListOrInt* r = &(right);

            if (!_isList) {
                l = new ListOrInt(true);
                ListOrInt temp(false);
                temp.setIntValue(_intValue);
                l->addItem(temp);
            } if (!right._isList) {
                r = new ListOrInt(true);
                ListOrInt temp(false);
                temp.setIntValue(right._intValue);
                r->addItem(temp);
            }

            std::vector<ListOrInt> leftList = l->getListValue();
            std::vector<ListOrInt> rightList = r->getListValue();

            for (int i = 0; i < leftList.size(); i++) {
                if (i >= rightList.size()) {
                    return -1;
                }
                int result = leftList[i].compareTo(rightList[i]);
                if (result != 0) {
                    return result;
                }
            }

            if (leftList.size() < rightList.size()) {
                return 1;
            } else {
                return 0;
            }
        }

};

#endif