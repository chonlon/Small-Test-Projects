#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/date_time/date.hpp>
#include <unistd.h>
#include <sys/types.h>
#if __GLIBC__ == 2 && __GLIBC_MINOR__ < 30
#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)
#endif

using namespace boost;
using namespace std;

boost::thread thread_obj;
boost::thread thread_obj1;

void func(void)
{
    char x;
    cout << "enter y to interrupt" << endl;
    cin >> x;
     pid_t tid = gettid();
    cout << "tid:" << tid << endl;
    if (x == 'y') {
        cout << "x = 'y'" << endl;    
        cout << "thread interrupt" << endl;
    }
}

void real_main() {

   cout << "real main thread" << endl;
    pid_t tid = gettid();
    cout << "tid:" << tid << endl;

    boost::system_time const timeout = boost::get_system_time() + boost::posix_time::seconds(3);
    try {
        boost::this_thread::sleep(timeout);
    }
    catch (boost::thread_interrupted &) {
        cout << "thread interrupted" << endl;
    }

}

int main()
{
    thread_obj1 = boost::thread(&func);
    thread_obj = boost::thread(&real_main);
    thread_obj.join();
}