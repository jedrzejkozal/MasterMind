#include "IAlleles.hpp"

class DefaultAlleles : public IAlleles
{
public:
    DefaultAlleles(const unsigned &allelesSize,
                   unsigned minAllelesValue,
                   unsigned maxAllelesValue);
    virtual ~DefaultAlleles() = default;

    virtual std::shared_ptr<IAlleles> copy() override;

    virtual void switch_allele_at(std::vector<unsigned>::iterator &iterator) override;
    virtual unsigned size() const override;

    virtual AllelesIterators iterators() override;
    virtual AllelesConstIterators constIterators() const override;
    virtual AllelesReverseIterators reverseIterators() override;

protected:
    std::vector<unsigned> alleles;
    unsigned minAllelesValue;
    unsigned maxAllelesValue;
};
