#include "cstdio"
#include "sstream"

int main() {
	double count = .1;
	count += .2;
	std::stringstream printstr;
	printstr << "Count: " << count << "\r";
	printf("%s", printstr.str().c_str());
	return 0;
}
