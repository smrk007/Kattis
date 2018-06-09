#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <vector>

//////////////////////////////////////////////////
class Doll {
private:
	int height;
	int diameter;
	int width;
public:
	// Initialization
	Doll (int h, int d, int w) {
		height = h;
		diameter = d;
		width = w;
	}
	Doll () {
		// Dummy initializer
	}
	
	// Accessors
	int getHeight () const { return height; }
	int getDiameter () const { return diameter; }
	int getWidth () const { return width; }

	// Comparison
	bool has_relation (Doll other_doll) const;
	void print() const {
		std::cout << "Doll: " << height << " " << diameter << " " << width << std::endl;
	}
	bool operator== (Doll other) const {
		bool condition1 = height == other.getHeight();
		bool condition2 = diameter == other.getDiameter();
		bool condition3 = width == other.getWidth();
		return condition1 && condition2 && condition3;
	}
	bool operator< (const Doll other) const {
		getHeight() < other.getHeight();
	}
	bool operator> (const Doll other) const {
		getHeight() > other.getHeight();
	}
};
//////////////////////////////////////////////////



//////////////////////////////////////////////////
class CounterChain {
private:
	Doll base;
	std::queue<Doll> red_pool_queue, blue_pool_queue;
 	std::vector<Doll> red_pool, blue_pool;
public:
	// Initialization
	CounterChain (Doll b) {
		base = b;
	}

	int size() { return red_pool.size() + blue_pool.size(); }
	Doll getBase() { return base; }
	Doll getRedPool { return red_pool; }
	Doll getBluePool { return blue_pool; }
	void fill (std::list<Doll>& white_pool);
	void print_and_erase() {
		// Ensure that the vector is sorted
		std::sort(red_pool.rbegin(),red_pool.rend());
		std::sort(blue_pool.rbegin(),blue_pool.rend());
		// Print red pool
		while (!red_pool.empty()) {
			red_pool.back().print();
			red_pool.pop_back();
		}
		std::cout << "-" << std::endl;
		// Print blue pool
		while (!blue_pool.empty()) {
			blue_pool.back().print();
			blue_pool.pop_back();
		}
		std::cout << std::endl;
	}
	int delta_value() {
		return red_pool.size() - blue_pool.size();
	}
	void flip_pool() {
		std::vector<Doll> hold = red_pool;
		red_pool = blue_pool;
		blue_pool = red_pool;
	}
	void insert_counter_chain (CounterChain other) {
		std::vector<Doll> red_hold = other.getRedPool();
		std::vector<Doll> blue_hold = other.getBluePool();
		
		while (!red_hold.empty()) {
			red_pool.push_back(red_hold.back());
			red_hold.pop_back();
		}

		while (!blue_hold.empty()) {
			blue_pool.push_back(blue_hold.back());
			blue_hold.pop_back();
		}

	}
};

CounterChain subset_sum(int No2, std::vector<CounterChain>) {
	
	


}

//////////////////////////////////////////////////

int solve_problem (int dolls_per_set) {

	//////////////////////////////////////////////////
	// The list of Dolls that could be put in either
	// set
	std::list<Doll> purple_pool;
	// The list of Dolls that have not yet been put in
	// either set
	std::list<Doll> white_pool;
	// The list of counter_chain groups (sets of dolls
	// that cannot be in the same set as one another)
	std::list<CounterChain> counter_chain_pool;
	//////////////////////////////////////////////////

	//////////////////////////////////////////////////
	// Loading each specified doll into the pool
	for (int i = 0; i < 2*dolls_per_set; i++) {
		int height, diameter, width;
		std::cin >> height >> diameter >> width;
		white_pool.push_back(Doll(height,diameter,width));
	}
	//////////////////////////////////////////////////
	
	// Creating the counter_chains
	while (!white_pool.empty()) {

		// Taking the next element in the white pool
		CounterChain nextChain = CounterChain(white_pool.front());
		white_pool.pop_front();
		
		// Filling the counter chain
		nextChain.fill(white_pool);
		counter_chain_pool.push_back(nextChain);
	}
	
	// Populating the master chain
	// TODO: Populate that shit

	// Finding the sum of the counter chains
	int sum = 0;
	for (int i = 0; i < counter_chain_pool.size(); i++) {
		if (counter_chain_pool.at(i).delta_value() < 0) {
			counter_chain_pool.at(i).flip_pool();
		}
		sum += cc.delta_value();
	}

	CounterChain output = subset_sum(sum/2, counter_chain_pool);

	return 0;
}

bool Doll::has_relation (Doll other_doll) const {
// TODO: Test has_relation
	//////////////////////////////////////////////////
	// Tests if either doll can fit within the other,
	// and hence is capable of being in the same set
	// of dolls.
	//////////////////////////////////////////////////
	
	// Testing if other fits in self


	int hollow_height = height - 2*width;
	int hollow_diameter = diameter - 2*width;
	bool condition1 = hollow_height >= other_doll.getHeight();
	bool condition2 = hollow_diameter >= other_doll.getDiameter();
	if (condition1 && condition2) {
		return true;
	}
	
	// Testing if self fits in other
	// Will only run if case 1 case failed
	int other_hollow_height = other_doll.getHeight() - 2*other_doll.getWidth();
	int other_hollow_diameter = other_doll.getDiameter() - 2*other_doll.getWidth();
	condition1 = other_hollow_height >= height;
	condition2 = other_hollow_diameter >= diameter;
	if (condition1 && condition2) {
		return true;
	}

	return false;
}

int main() {
	
	// Load the number of dolls per set
	int n;
	std::cin >> n;

	// Testing all the cases until none
	while (n != 0) {
		solve_problem(n);
		std::cin >> n;
	}

	return 0;
}

void CounterChain::fill (std::list<Doll>& white_pool) {

	//////////////////////////////////////////////////
	// Arbitrarilly let the first element go into the
	// red pool
	red_pool_queue.push(base);
	//////////////////////////////////////////////////
	
	while ( !red_pool_queue.empty() || !blue_pool_queue.empty() ) {
		std::list<Doll>::iterator doll_iterator;

		while ( !red_pool_queue.empty() ) {
			// Load the next in the red queue
			Doll temp = red_pool_queue.front();
			red_pool_queue.pop();

			// Load counters to temp
			doll_iterator = white_pool.begin();
			while (doll_iterator != white_pool.end()) {
		
				if (!doll_iterator->has_relation(temp)) {
					blue_pool_queue.push(*doll_iterator);
					doll_iterator = white_pool.erase(doll_iterator);
				} else {
					doll_iterator++;
				}
			} 
		
			// Finalize element
			red_pool.push_back( temp );
		}

		while ( !blue_pool_queue.empty() ) {
			// Load the next in the blue queue
			Doll temp = blue_pool_queue.front();
			blue_pool_queue.pop();

			// Load counters to temp
			doll_iterator = white_pool.begin();
			while (doll_iterator != white_pool.end()) {
				if (!doll_iterator->has_relation(temp)) {
					red_pool_queue.push(*doll_iterator);
					doll_iterator = white_pool.erase(doll_iterator);
				} else {
					doll_iterator++;
				}
			} 

			// Finalize element
			blue_pool.push_back( temp );
		}
	}
}
