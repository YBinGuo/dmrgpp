#ifndef KRONECKERDUMPER_H
#define KRONECKERDUMPER_H
#include "Vector.h"
#include "TypeToString.h"
#include <fstream>
#include "../Version.h"

namespace Dmrg {

template<typename LeftRightSuperType>
class KroneckerDumper {

	typedef typename LeftRightSuperType::BasisWithOperatorsType BasisWithOperatorsType;
	typedef typename BasisWithOperatorsType::SparseMatrixType SparseMatrixType;
	typedef typename PsimagLite::Vector<bool>::Type VectorBoolType;
	typedef typename PsimagLite::Vector<SizeType>::Type VectorSizeType;

public:

	struct ParamsForKroneckerDumper {
		ParamsForKroneckerDumper(bool enable = false, SizeType b = 0, SizeType e = 0)
		    : enabled(enable),begin(b),end(e)
		{}

		bool enabled;
		SizeType begin;
		SizeType end;
	}; // struct ParamsForKroneckerDumper

	KroneckerDumper(const ParamsForKroneckerDumper* p,
	                const LeftRightSuperType& lrs,
	                SizeType m)
	    : enabled_(p && p->enabled)
	{
		if (!enabled_) return;
		bool b = (p->end > 0 && counter_ >= p->end);
		if (counter_ < p->begin || b) {
			counter_++;
			enabled_ = false;
			return;
		}

		PsimagLite::String filename = "kroneckerDumper" + ttos(counter_) + ".txt";
		fout_.open(filename.c_str());
		fout_<<"#KroneckerDumper for DMRG++ version "<<DMRGPP_VERSION<<"\n";
		fout_<<"#Instance="<<counter_<<"\n";
		fout_<<"#LeftBasis\n";
		fout_<<lrs.left();
		fout_<<"#RightBasis\n";
		fout_<<lrs.right();
		fout_<<"#SuperBasis\n";
		fout_<<lrs.super();
		fout_<<"M_Sector="<<m<<"\n";
		counter_++;
	}

	~KroneckerDumper()
	{
		fout_<<"#EOF\n";
		fout_.close();
	}

	void push(const SparseMatrixType& A, const SparseMatrixType& B)
	{
		if (!enabled_) return;

		fout_<<"#START_AB_PAIR\n";
		fout_<<"#A\n";
		fout_<<A;
		fout_<<"#B\n";
		fout_<<B;
		fout_<<"#END_AB_PAIR\n";
	}

	void push(bool option,const SparseMatrixType& hamiltonian)
	{
		if (!enabled_) return;
		if (option)
			fout_<<"#LeftHamiltonian\n";
		else
			fout_<<"#RightHamiltonian\n";
		fout_<<hamiltonian;
	}

private:

	static SizeType counter_;
	bool enabled_;
	std::ofstream fout_;
}; // class KroneckerDumpter

template<typename SparseMatrixType>
SizeType KroneckerDumper<SparseMatrixType>::counter_ = 0;

} // namespace Dmrg
#endif // KRONECKERDUMPER_H
