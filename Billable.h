#ifndef SENECA_BILLABLE_H
#define SENECA_BILLABLE_H
#include <iostream>
#include <fstream>
namespace seneca {
	class Billable {
	protected:
		char* m_name;
		double m_price;
		void price(double value);
		void name(const char* name);

	public:

		Billable();
		virtual ~Billable();
		Billable(const Billable& bill);
		Billable& operator=(const Billable& bill);

		virtual double price() const;
		virtual std::ostream& print(std::ostream& ostr = std::cout) const = 0;
		virtual bool order() = 0;
		virtual bool ordered() const = 0;
		virtual std::ifstream& read(std::ifstream& file) = 0;


		friend double operator+(double money, const Billable& B);
		friend double& operator+=(double& money, const Billable& B);
		operator const char* () const;



	};
}
#endif // !SENECA_BILLABLE_H
