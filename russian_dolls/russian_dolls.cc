#include <iostream>
#include <list>
#include <queue>

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
	int getHeight () { return height; }
	int getDiameter () { return diameter; }
	int getWidth () { return width; }

	bool has_relation (Doll other_doll);
	void print() {
		std::cout << "Doll: " << height << " " << diameter << " " << width << std::endl;
	}
	bool operator== (Doll other) {
		bool condition1 = height == other.getHeight();
		bool condition2 = diameter == other.getDiameter();
		bool condition3 = width == other.getWidth();
		return condition1 && condition2 && condition3;
	}
};
//////////////////////////////////////////////////



//////////////////////////////////////////////////
class CounterChain {
private:
	Doll base;
	std::queue<Doll> red_pool_queue, blue_pool_queue;
	std::list<Doll> red_pool, blue_pool;
public:
	// Initialization
	CounterChain (Doll b) {
		base = b;
	}

	int size() { return red_pool.size() + blue_pool.size(); }
	Doll getBase() { return base; }
	void fill (std::list<Doll>& white_pool);
};
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
		
		// Dealing with the outcome of .fill()
		if ( nextChain.size() == 1 ) {
			purple_pool.push_back(nextChain.getBase());
		} else {
			counter_chain_pool.push_back(nextChain);
		}
	}
		
	std::cout << counter_chain_pool.size() << std::endl;
	
	// Populating the master chain
	// TODO: Populate that shit

	return 0;
}

bool Doll::has_relation (Doll other_doll) {
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
		
				if (temp == Doll(97, 97, 3)) {
					doll_iterator->print();
				}
				
				if (doll_iterator->has_relation(temp)) {
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
				if (doll_iterator->has_relation(temp)) {
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
