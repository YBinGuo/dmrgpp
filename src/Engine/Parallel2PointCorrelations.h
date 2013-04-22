/*
Copyright (c) 2009,-2012 UT-Battelle, LLC
All rights reserved

[DMRG++, Version 2.0.0]
[by G.A., Oak Ridge National Laboratory]

UT Battelle Open Source Software License 11242008

OPEN SOURCE LICENSE

Subject to the conditions of this License, each
contributor to this software hereby grants, free of
charge, to any person obtaining a copy of this software
and associated documentation files (the "Software"), a
perpetual, worldwide, non-exclusive, no-charge,
royalty-free, irrevocable copyright license to use, copy,
modify, merge, publish, distribute, and/or sublicense
copies of the Software.

1. Redistributions of Software must retain the above
copyright and license notices, this list of conditions,
and the following disclaimer.  Changes or modifications
to, or derivative works of, the Software should be noted
with comments and the contributor and organization's
name.

2. Neither the names of UT-Battelle, LLC or the
Department of Energy nor the names of the Software
contributors may be used to endorse or promote products
derived from this software without specific prior written
permission of UT-Battelle.

3. The software and the end-user documentation included
with the redistribution, with or without modification,
must include the following acknowledgment:

"This product includes software produced by UT-Battelle,
LLC under Contract No. DE-AC05-00OR22725  with the
Department of Energy."

*********************************************************
DISCLAIMER

THE SOFTWARE IS SUPPLIED BY THE COPYRIGHT HOLDERS AND
CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
COPYRIGHT OWNER, CONTRIBUTORS, UNITED STATES GOVERNMENT,
OR THE UNITED STATES DEPARTMENT OF ENERGY BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
DAMAGE.

NEITHER THE UNITED STATES GOVERNMENT, NOR THE UNITED
STATES DEPARTMENT OF ENERGY, NOR THE COPYRIGHT OWNER, NOR
ANY OF THEIR EMPLOYEES, REPRESENTS THAT THE USE OF ANY
INFORMATION, DATA, APPARATUS, PRODUCT, OR PROCESS
DISCLOSED WOULD NOT INFRINGE PRIVATELY OWNED RIGHTS.

*********************************************************


*/
/** \ingroup DMRG */
/*@{*/

/*! \file Parallel2PointCorrelations.h
 *
 * DOC TBW FIXME
 */
#ifndef PARALLEL_2POINT_CORRELATIONS_H
#define PARALLEL_2POINT_CORRELATIONS_H

#include "Matrix.h"

namespace Dmrg {

template<typename RealType_,typename TwoPointCorrelationsType>
class Parallel2PointCorrelations {

	typedef std::pair<size_t,size_t> PairType;
	typedef typename TwoPointCorrelationsType::MatrixType MatrixType;
	typedef typename MatrixType::value_type FieldType;

public:

	typedef RealType_ RealType;

	Parallel2PointCorrelations(MatrixType& w,
							   TwoPointCorrelationsType& twopoint,
							   const std::vector<PairType>& pairs,
							   const MatrixType& O1,
							   const MatrixType& O2,
							   int fermionicSign)
		: w_(w),
		  twopoint_(twopoint),
		  pairs_(pairs),
		  O1_(O1),
		  O2_(O2),
		  fermionicSign_(fermionicSign)
	{}

	void thread_function_(size_t threadNum,size_t blockSize,size_t total,pthread_mutex_t* myMutex)
	{
		for (size_t p=0;p<blockSize;p++) {
			size_t px = threadNum * blockSize + p;
			if (px>=total) continue;

			size_t i = pairs_[px].first;
			size_t j = pairs_[px].second;
			size_t threadId = (myMutex==0) ? 0 : threadNum;
			w_(i,j) = twopoint_.calcCorrelation(i,j,O1_,O2_,fermionicSign_,threadId);
		}
	}

private:

	MatrixType& w_;
	TwoPointCorrelationsType& twopoint_;
	const std::vector<PairType>& pairs_;
	const MatrixType& O1_;
	const MatrixType& O2_;
	int fermionicSign_;
}; // class Parallel2PointCorrelations
} // namespace Dmrg 

/*@}*/
#endif // PARALLEL_2POINT_CORRELATIONS_H
