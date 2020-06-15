#include "1.pb.h"
#include "google/protobuf/service.h"
#include "google/protobuf/stubs/common.h"
#include <google/protobuf/stubs/callback.h>

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution
{
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *result = new ListNode{0};
        ListNode *current_node = result;
        ListNode *last_one;
        int carry = 0;

        auto cal = new auto([&carry, &last_one](int _current_result, ListNode **_current_node) -> void {
            _current_result += carry;
            if (_current_result > 10)
            {
                carry = 1;
                _current_result %= 10;
            }
            else
            {
                carry = 0;
            }
            (*_current_node)->val = _current_result;
            (*_current_node)->next = new ListNode{0};
            last_one = *_current_node;
            *_current_node = (*_current_node)->next;
        });

        while (l1 && l2)
        {
            auto current_result = l1->val + l2->val;

            (*cal)(current_result, &current_node);

            l1 = l1->next;
            l2 = l2->next;
        }

        while (l1)
        {
            *cal(l1->val, &current_node);
            l1 = l1->next;
        }

        while (l2)
        {
            *cal(l2->val, &current_node);
            l2 = l2->next;
        }

        delete current_node;
        last_one->next = nullptr;
        return result;
    }
};
class PersonService
    : public ::google::protobuf::Service
{
    virtual void upload(::google::protobuf::RpcController* controller,
        const ::tutorial::Person* person,
        ::tutorial::PersonResponse* response,
        ::google::protobuf::Closure* done
    )
    {
        controller->SetFailed("Failed");
        done->Run();
    }
};

int main() {
    return 0;
}