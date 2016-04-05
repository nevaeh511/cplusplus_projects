// Aaron Merrill
// CS 3370

#include <atomic>
#include <condition_variable>
#include <cstdlib>
#include <fstream>
#include <future>       // For async
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <sstream>
using namespace std;

int const MAX = 10;
int groupCount[MAX];
ofstream output[MAX];

class ProducerConsumer {
    static queue<int> q;
	static queue<int> f;
    static condition_variable q_cond;
    static mutex q_sync, print, f_sync;
	
public:
	static size_t nprods, ncons;
	static atomic_size_t nprod;
	static const size_t ngroups = 10;
    static atomic_bool quit;

    static void consume() {
        for (;;) {
            // Get lock for sync mutex
            unique_lock<mutex> qlck(q_sync);

            // Wait for queue to have something to process
            q_cond.wait(qlck,[](){return !q.empty() || !nprod.load();});
            if (q.empty() && !nprod.load())
                break;
            auto x = q.front();
			q.pop();
            qlck.unlock();
			
			if (x % 3 != 0){
				lock_guard<mutex> flck(f_sync);
				f.push(x);
			}
        }
    }

     static void produce(int i) {
        // Generate random ints indefinitely
        srand(time(nullptr)+i);
        for (;;) {
            // See if it's time to quit
            if (quit.load())
                break;

            int n = rand();     // Get random int

            // Get lock for sync mutex; push int
            unique_lock<mutex> slck(q_sync);
            q.push(n);
            slck.unlock();
            q_cond.notify_one();
        }

        // Notify consumers that a producer has shut down
        --nprod;
        q_cond.notify_all();
    }

	static void consumeForGroups(int val){
		for(;;){
			unique_lock<mutex> flck(f_sync);
            if (f.empty()){
                break;
			}
			auto num = f.front();
			f.pop();
			flck.unlock();
			
			size_t groupNum = num % 10;
			
			if(groupNum == val){
				output[val] << num << endl;
				groupCount[val]++;
			}
		}
	}
};

queue<int> ProducerConsumer::q, ProducerConsumer::f;
size_t ProducerConsumer::nprods, ProducerConsumer::ncons;
condition_variable ProducerConsumer::q_cond;
mutex ProducerConsumer::q_sync, ProducerConsumer::print, ProducerConsumer::f_sync;
atomic_bool ProducerConsumer::quit;
atomic_size_t ProducerConsumer::nprod;

void input() {
    cout << "Press Enter when ready...";
    cin.get();
}

int main(int argc, char* argv[])
{
	int total_args = 3;
	int arg1 = atoi(argv[1]);
	int arg2 = atoi(argv[2]);
	if (argc == 0){
		cerr << "Please enter your program name "
			<< "followed by two numbers." << endl;
	}
	else if (argc != 3){
		cerr << "Please enter two numbers." << endl;
	}
	else{
		ProducerConsumer::nprods = arg1;
		ProducerConsumer::ncons = arg2;
		ProducerConsumer::nprod = ProducerConsumer::nprods;
	}
	
	for(int i = 0; i < MAX; ++i){
		groupCount[i] = 0;
		ostringstream os;
		os << "group" << i << ".out";
		output[i].open(os.str());
	}
	
    vector<thread> prods, cons, groups;
	for (size_t i = 0; i < ProducerConsumer::ncons; ++i)
        cons.push_back(thread(&ProducerConsumer::consume));
	for (size_t i = 0; i < ProducerConsumer::nprods; ++i)
        prods.push_back(thread(&ProducerConsumer::produce,i));

    auto response = async(input);
    response.get();
    ProducerConsumer::quit = true;

    // Join all threads
    for (auto &p: prods)
        p.join();
    for (auto &c: cons)
        c.join();
	
	for (size_t i = 0; i < ProducerConsumer::ngroups; ++i)
		groups.push_back(thread(&ProducerConsumer::consumeForGroups, i));
	
	for (auto &g : groups)
		g.join();
	
	for(int i = 0; i < MAX; ++i){
		cout << "Group" << i << ": " << groupCount[i] << " numbers." << endl;
	}
}

/*
The most challenging with this program was figuring out the threading syntax, the logic
of the mutex locks not knowing where to place them.
I do like the concept behind multi-threading. 
*/