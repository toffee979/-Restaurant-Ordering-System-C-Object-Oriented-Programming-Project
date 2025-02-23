#ifndef SENECA_DRINK_H
#define SENECA_DRINK_H
#include "Billable.h"

namespace seneca {
	class Drink : public Billable {

		char m_size = '\0';

	public:

		Drink();

		std::ostream& print(std::ostream& ostr = std::cout) const override;
		bool order() override;
		bool ordered() const override;
		std::ifstream& read(std::ifstream& read) override;
		double price() const override;

	};
}
#endif // !SENECA_DRINK_H


