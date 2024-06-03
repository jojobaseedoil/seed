#ifndef ID_MANAGER_H
#define ID_MANAGER_H

#include <vector>
#include <queue>

class IDManager
{
public:
    IDManager(int size=32);

    /* get next free id */
    int Next();
    /* return an unused id */
    void Refund(int id);
    /* check if has any id available */
    bool HasNext() const;

private:
    std::vector<bool> mUsed;
    std::queue<int> mIds;
    int mSize;
};

#endif // ID_MANAGER_H