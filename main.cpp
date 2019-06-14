#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool Read(vector<char> &Vec, const char* File_name)
{
	ifstream RawText(File_name, ifstream::in);

	if (RawText.is_open())
	{
		char temp = 0;
		int i = 0;
		RawText.seekg(0, RawText.end);
		i = RawText.tellg();
		Vec.reserve(i);
		RawText.seekg(0, RawText.beg);
		while (i--)
		{
			temp = RawText.get();
			if ((temp > 64 && temp < 91) || (temp > 96 && temp < 123) || temp == 32) Vec.emplace_back(temp);
		}
		RawText.close();
		return 0;
	}
	else
	{
		cout << "Error, cannot find \"" << File_name << "\"" << endl;
		return 1;
	}
}

bool is_prime(unsigned long int number)
{
	const unsigned long long int SIZE = number + 2;
	bool* temp_array = new bool[SIZE]; // tablica booleanów 

	for (int i = 2; i < SIZE; i++) // zerowanie tablicy
		temp_array[i] = 0;

	for (int i = 2; i*i < SIZE; i++)
	{
		if (!temp_array[i])
		{
			for (int j = i * i; j < SIZE; j += i)
				temp_array[j] = 1;
		}
	}
	if (temp_array[number])
	{
		return false;
	}
	return true;
}

void PrintVecChar(vector<char>& vec)
{
	for (auto& v : vec)
		cout << v;
	cout << endl;
}

vector<unsigned int> operator+(vector<unsigned int> lhs, vector<unsigned int> rhs)
{
	lhs.insert(lhs.end(), rhs.begin(), rhs.end());
	return lhs;
}

vector<unsigned int> Fermat_Part2(unsigned long int a)
{
	int y = 0;
	unsigned int x = static_cast<unsigned int>(sqrt(a));
	if (x == sqrt(a))
	{
		return  Fermat_Part2(x) + Fermat_Part2(x);
	}
	while (++x < (a + 1) / 2)
	{
		y = x * x - a;
		if (y > 0 && (static_cast<unsigned int>(sqrt(y)) == sqrt(y)))
		{
			y = static_cast<unsigned int>(sqrt(y));
			return Fermat_Part2(x + y) + Fermat_Part2(x - y);
		}
	}
	return vector<unsigned int>{ a };
}

unsigned int Fermat(unsigned long int a)
{
	vector<unsigned int> result;
	result.reserve(128);
	while (!((a >> 0) & 1))
	{
		result.emplace_back(2);
		a >>= 1;
	}
	result = result + Fermat_Part2(a);
	sort(result.begin(), result.end());
	result.erase(unique(result.begin(), result.end()), result.end());
	reverse(result.begin(), result.end());
	return result[0];
}

unsigned long long int fast_mod(unsigned long int a, unsigned long long int b, unsigned int mod, unsigned int n = 0)
{
	unsigned long long int temp = 1;
	if (n > 0)
	{
		if ((temp << n - 1) > b) return 1;
		a = (a * a) % mod;
	}
	n++;
	if ((b >> n - 1) & 1) return (a * fast_mod(a, b, mod, n)) % mod;
	return fast_mod(a, b, mod, n);
}

unsigned long int value_of_text(vector<char> &vec)
{
	unsigned long int temp = 0;
	for (auto& c : vec)
	{
		if (c == 32) 
			temp += 42;
		else 
			temp += static_cast<unsigned long int>(c);
	}
	return temp;
}

int main()
{
	long float p, g, k, r;
	long int q = 0, n1 = 0, n2 = 0, sp = 0;
	long int gk, jha;
	vector<char> Text;
	if (Read(Text, "text.txt"))
		return 1;
	PrintVecChar(Text);
	cin >> p;
	if (!is_prime(p))
	{
		cout << "p is not a prime number!" << endl;
		return 1;
	}
	q = Fermat(p - 1);
	for (auto& c : Text)
	{
		if (c == ' ')
			sp++;
		else if (c == 'a' || c == 'e' || c == 'i' || c == 'u' || c == 'o'
			|| c == 'A' || c == 'E' || c == 'I' || c == 'U' || c == 'O')
			n1++;
		else
			n2++;
	}
	if (7 * n1 - 3 * n2 + sp * sp < 0)
		jha = fast_mod((p + 1)/q, (7 * n1 - 3 * n2 + sp * sp) * -1, p);
	else
		jha = fast_mod(q, 7 * n1 - 3 * n2 + sp * sp, p);
	cout << "JHA: " << jha << endl;
	cin >> g;
	cin >> k;
	cin >> r;
	cout << "---PRK---" << endl;
	gk = fast_mod(g, k, p);
	cout << "(" << gk << ", " << g << ", " << p << ", " << q << ")\t";
	cout << "(" << gk % q << ", " << ((value_of_text(Text) + gk % q) % q) << ")" << endl;

	cin >> q;
	return 0;
}
