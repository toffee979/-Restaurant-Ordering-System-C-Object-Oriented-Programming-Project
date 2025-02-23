#ifndef SENECA_FOOD_H
#define SENECA_FOOD_H
#include "Billable.h"
namespace seneca {
	class Food : public Billable {
		bool m_ordered;
		bool m_child;
		char* m_customize;

	public:
		Food();
		~Food();
		Food(const Food& food);
		Food& operator=(const Food& food);

		std::ostream& print(std::ostream& ostr = std::cout) const override;
		bool order() override;
		bool ordered() const override;
		std::ifstream& read(std::ifstream& read) override;
		double price() const override;
	};
}
#endif // !SENECA_FOOD_H


