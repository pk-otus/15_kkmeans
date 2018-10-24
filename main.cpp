#include <iostream>
#include <vector>

#include <dlib/clustering.h>

using namespace std;
using namespace dlib;

using sample_type = matrix<double, 2, 1>;
using kernel_type = radial_basis_kernel<sample_type>;

int main(int argc, char const *argv[])
{
	if (argc < 2)
	{
		std::cout << "Usage: kkmeans <number of clusters>";
		return 1;
	}

	const int num_clusters = stoi(argv[1]);

	std::vector<sample_type> samples;
	sample_type m;
	for (std::string line; std::getline(std::cin, line);)
	{
		auto pos_delimiter = line.find(';');
		m(0) = stod(line.substr(0, pos_delimiter));
		m(1) = stod(line.substr(pos_delimiter + 1));
		samples.push_back(m);
	}

	kcentroid<kernel_type>		kc(kernel_type(0.00001), 0.01, 8);
	kkmeans<kernel_type>		test(kc);
	std::vector<sample_type>	initial_centers;

	test.set_number_of_centers(num_clusters);

	pick_initial_centers(num_clusters, initial_centers, samples, test.get_kernel());

	test.train(samples, initial_centers);

	for (const auto& s : samples)
	{
		cout << s(0) << ';' << s(1) << ";cluster" << test(s) << '\n';
	}

	return 0;
}


