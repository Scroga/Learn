#include <iostream>

void pp(int &i)
{
	std::cout << &i << " " << i << " " << sizeof(i) << "\n";
} 

template <typename T>
class DynamicArray
{
	size_t m_size;
	T * m_arr;

public:
	DynamicArray(size_t size)
		: m_size(size)
		, m_arr(new T[size])
	{
		std::fill_n(m_arr, m_size, T());
		std::cout << "Array Constructor\n";
	}

	~DynamicArray()
	{
		delete[] m_arr;
		std::cout << "Array Destructor\n";
	}

	T get(size_t index) const
	{
		return m_arr[index];
	}

	void set(size_t index, T val)
	{
		m_arr[index] = val;
	}

	void print() const
	{
		for(size_t i = 0; i < m_size; i++)
		{
			std::cout << i << " " << m_arr[i] << "\n";
		}
	}



	const T& operator [] (size_t index) const
	{
		return m_arr[index];
	}

	T& operator [] (size_t index)
	{
		return m_arr[index];
	}
};

int main(int argc, char * argv[])
{
	DynamicArray<float> myArr(10);

	//myArr[3] = 10.344f;
	//myArr[7] = 3.14f;

	std::cout << myArr[2] << "\n";

	myArr[2] = 13;

	myArr.print();

	return 0;
}