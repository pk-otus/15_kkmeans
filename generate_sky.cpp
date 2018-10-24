#include <fstream>
#include <dlib/rand.h>

using namespace std;
using namespace dlib;

void log(ofstream& fout, double x, double y)
{
	fout << x << ';' << y << '\n';
}

int main(int argc, char const *argv[])
{
	if (argc < 2)
	{
		std::cout << "Usage: generate_sky <filename>";
		return 1;
	}

	double x, y;

	dlib::rand rnd;

	const long num = 200;

	ofstream fout(argv[1]);

	for (long i = 0; i < num; ++i)
	{
		x = 200 * rnd.get_random_double() - 100;
		y = 200 * rnd.get_random_double() - 100;

		log(fout, x, y);

	}

	fout.close();
	return 0;
}