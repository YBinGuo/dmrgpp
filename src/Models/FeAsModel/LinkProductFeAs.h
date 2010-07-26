// BEGIN LICENSE BLOCK
/*
Copyright � 2009 , UT-Battelle, LLC
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
// END LICENSE BLOCK
/** \ingroup DMRG */
/*@{*/

/*! \file LinkProductFeAs.h
 *
 *  A class to represent product of operators that form a link or bond for this model
 *
 */
#ifndef LINK_PRODUCT_H
#define LINK_PRODUCT_H

namespace Dmrg {
	
	template<typename ModelHelperType>
	class LinkProductFeAs {
			typedef typename ModelHelperType::SparseMatrixType SparseMatrixType;
			typedef typename SparseMatrixType::value_type SparseElementType;
			typedef std::pair<size_t,size_t> PairType;
			
		public:
			typedef typename ModelHelperType::RealType RealType;
			//typedef LinkProductStruct<SparseElementType> LinkProductStructType;
			
			static size_t dofs() { return 8; }
			
			// has only dependence on orbital
			static PairType connectorDofs(size_t dofs,size_t term)
			{
				size_t spin = dofs/4;
				size_t xtmp = (spin==0) ? 0 : 4;
				xtmp = dofs - xtmp;
				size_t orb1 = xtmp/2;
				size_t orb2 = (xtmp & 1);
				return PairType(orb1,orb2); // has only dependence on orbital
			}
			
			static void setLinkData(
					size_t dofs,
     					bool isSu2,
					size_t& fermionOrBoson,
					PairType& ops,
     					std::pair<char,char>& mods,
					size_t& angularMomentum,
     					RealType& angularFactor,
					size_t& category)
			{
				fermionOrBoson = ProgramGlobals::FERMION;
				size_t spin = getSpin(dofs);
				ops = operatorDofs(dofs);
				angularFactor = 1;
				if (spin==1) angularFactor = -1;
				angularMomentum = 1;
				category = spin;
			}
			
			static void valueModifier(SparseElementType& value,size_t dofs,bool isSu2)
			{
			}
		private:
			// spin is diagonal
			static std::pair<size_t,size_t> operatorDofs(size_t dofs)
			{
				size_t spin = dofs/4;
				size_t xtmp = (spin==0) ? 0 : 4;
				xtmp = dofs - xtmp;
				size_t orb1 = xtmp/2;
				size_t orb2 = (xtmp & 1);
				size_t op1 = orb1 + spin*2;
				size_t op2 = orb2 + spin*2;
				return std::pair<size_t,size_t>(op1,op2);
			}
			
			static size_t getSpin(size_t dofs)
			{
				return dofs/4;
			}
	}; // class LinkPRoductFeAs
} // namespace Dmrg
/*@}*/
#endif
