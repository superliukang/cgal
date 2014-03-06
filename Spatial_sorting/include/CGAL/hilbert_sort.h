// Copyright (c) 2007-2011  INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; either version 3 of the License,
// or (at your option) any later version.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL$
// $Id$
//
// Author(s)     : Christophe Delage
//               : Olivier Devillers

#ifndef CGAL_HILBERT_SORT_H
#define CGAL_HILBERT_SORT_H

#include <CGAL/basic.h>

#include <CGAL/Hilbert_policy_tags.h>
#include <CGAL/Hilbert_sort_2.h>
#include <CGAL/Hilbert_sort_3.h>
#include <CGAL/Hilbert_sort_d.h>
#include <CGAL/Hilbert_sort_on_sphere_3.h>

#include <boost/random/random_number_generator.hpp>
#include <boost/random/linear_congruential.hpp>

#include <algorithm>

namespace CGAL {


namespace internal {

  template <class RandomAccessIterator, class Kernel, class Policy>
    void hilbert_sort (RandomAccessIterator begin, 
		       RandomAccessIterator end,
                       const Kernel &k, 
		       Policy /*policy*/,
		       typename Kernel::Point_2 *)
    {
        boost::rand48 random;
        boost::random_number_generator<boost::rand48> rng(random);
        std::random_shuffle(begin,end, rng);
	(Hilbert_sort_2<Kernel, Policy> (k))(begin, end);
    }
    
    template <class RandomAccessIterator, class Kernel, class Policy>
      void hilbert_sort (RandomAccessIterator begin, 
			 RandomAccessIterator end,
                         const Kernel &k, 
			 Policy /*policy*/,
			 typename Kernel::Point_3 *)
    {
        boost::rand48 random;
        boost::random_number_generator<boost::rand48> rng(random);
        std::random_shuffle(begin,end, rng);
        (Hilbert_sort_3<Kernel, Policy> (k))(begin, end);
    }

    template <class RandomAccessIterator, class Kernel, class Policy>
      void hilbert_sort (RandomAccessIterator begin,
			 RandomAccessIterator end,
                         const Kernel &k, 
			 Policy /*policy*/,
			 typename Kernel::Point_d *)
    {
        boost::rand48 random;
        boost::random_number_generator<boost::rand48> rng(random);
        std::random_shuffle(begin,end, rng);
        (Hilbert_sort_d<Kernel, Policy> (k))(begin, end);
    }
    
	template <class RandomAccessIterator, class Kernel, class Policy>
      void hilbert_sort_on_sphere (RandomAccessIterator begin, 
			 RandomAccessIterator end,
             const Kernel &k, 
			 Policy,
			 typename Kernel::Point_3 *,
			 const typename Kernel::Sphere_3 &s)
    {
        boost::rand48 random;
        boost::random_number_generator<boost::rand48> rng(random);
        std::random_shuffle(begin,end, rng);
        (Hilbert_sort_on_sphere_3<Kernel, Policy> (k,s))(begin, end);
    }

}

template <class RandomAccessIterator>
void hilbert_sort (RandomAccessIterator begin, RandomAccessIterator end)
{

    typedef std::iterator_traits<RandomAccessIterator> ITraits;
    typedef typename ITraits::value_type               value_type;
    typedef CGAL::Kernel_traits<value_type>            KTraits;
    typedef typename KTraits::Kernel                   Kernel;

    internal::hilbert_sort(begin, end, Kernel(), Hilbert_sort_median_policy(),
				  static_cast<value_type *> (0));

}

template <class RandomAccessIterator, class Kernel>
void hilbert_sort (RandomAccessIterator begin, RandomAccessIterator end,
		   const Kernel &k)
{
    typedef std::iterator_traits<RandomAccessIterator> ITraits;
    typedef typename ITraits::value_type               value_type;
  
    internal::hilbert_sort(begin, end, k, Hilbert_sort_median_policy(),
				  static_cast<value_type *> (0));
}

  template <class RandomAccessIterator>
void hilbert_sort (RandomAccessIterator begin, RandomAccessIterator end,
		   Hilbert_sort_median_policy policy)
{
    typedef std::iterator_traits<RandomAccessIterator> ITraits;
    typedef typename ITraits::value_type               value_type;
    typedef CGAL::Kernel_traits<value_type>            KTraits;
    typedef typename KTraits::Kernel                   Kernel;

    internal::hilbert_sort(begin, end, Kernel(), policy,
				  static_cast<value_type *> (0));

}


  template <class RandomAccessIterator>
void hilbert_sort (RandomAccessIterator begin, RandomAccessIterator end,
		   Hilbert_sort_middle_policy policy)
{
    typedef std::iterator_traits<RandomAccessIterator> ITraits;
    typedef typename ITraits::value_type               value_type;
    typedef CGAL::Kernel_traits<value_type>            KTraits;
    typedef typename KTraits::Kernel                   Kernel;

    internal::hilbert_sort(begin, end, Kernel(), policy,
				  static_cast<value_type *> (0));

}


  template <class RandomAccessIterator, class Kernel, class Policy>
void hilbert_sort (RandomAccessIterator begin, RandomAccessIterator end,
		   const Kernel &k, Policy policy)
{
    typedef std::iterator_traits<RandomAccessIterator> ITraits;
    typedef typename ITraits::value_type               value_type;

    internal::hilbert_sort(begin, end, 
			   k, policy, static_cast<value_type *> (0));
}

template <class RandomAccessIterator>
void hilbert_sort_on_sphere (RandomAccessIterator begin, RandomAccessIterator end,
  const typename CGAL::Kernel_traits<typename std::iterator_traits<RandomAccessIterator>::value_type>::Kernel::Sphere_3 &s =
  typename CGAL::Kernel_traits<typename std::iterator_traits<RandomAccessIterator>::value_type>::Kernel::Sphere_3(
    typename CGAL::Kernel_traits<typename std::iterator_traits<RandomAccessIterator>::value_type>::Kernel::Point_3(
      typename CGAL::Kernel_traits<typename std::iterator_traits<RandomAccessIterator>::value_type>::Kernel::FT(0),
      typename CGAL::Kernel_traits<typename std::iterator_traits<RandomAccessIterator>::value_type>::Kernel::FT(0),
      typename CGAL::Kernel_traits<typename std::iterator_traits<RandomAccessIterator>::value_type>::Kernel::FT(0)
    ), typename CGAL::Kernel_traits<typename std::iterator_traits<RandomAccessIterator>::value_type>::Kernel::FT(1)))
{

    typedef std::iterator_traits<RandomAccessIterator> ITraits;
    typedef typename ITraits::value_type               value_type;
    typedef CGAL::Kernel_traits<value_type>            KTraits;
    typedef typename KTraits::Kernel                   Kernel;

    internal::hilbert_sort_on_sphere(begin, end, Kernel(), Hilbert_sort_median_policy(),
				  static_cast<value_type *> (0), s);

}

template <class RandomAccessIterator, class Kernel>
void hilbert_sort_on_sphere (RandomAccessIterator begin, RandomAccessIterator end, 
  const typename Kernel::Sphere_3 &s, const Kernel &k)
{
    typedef std::iterator_traits<RandomAccessIterator> ITraits;
    typedef typename ITraits::value_type               value_type;

    internal::hilbert_sort_on_sphere(begin, end, k, Hilbert_sort_median_policy(),
				  static_cast<value_type *> (0), s);
}

  template <class RandomAccessIterator>
void hilbert_sort_on_sphere (RandomAccessIterator begin, RandomAccessIterator end, Hilbert_sort_median_policy policy,
  const typename CGAL::Kernel_traits<typename std::iterator_traits<RandomAccessIterator>::value_type>::Kernel::Sphere_3 &s =
  typename CGAL::Kernel_traits<typename std::iterator_traits<RandomAccessIterator>::value_type>::Kernel::Sphere_3(
	typename CGAL::Kernel_traits<typename std::iterator_traits<RandomAccessIterator>::value_type>::Kernel::Point_3(
	typename CGAL::Kernel_traits<typename std::iterator_traits<RandomAccessIterator>::value_type>::Kernel::FT(0),
	typename CGAL::Kernel_traits<typename std::iterator_traits<RandomAccessIterator>::value_type>::Kernel::FT(0),
	typename CGAL::Kernel_traits<typename std::iterator_traits<RandomAccessIterator>::value_type>::Kernel::FT(0)
	), typename CGAL::Kernel_traits<typename std::iterator_traits<RandomAccessIterator>::value_type>::Kernel::FT(1)))
{
    typedef std::iterator_traits<RandomAccessIterator> ITraits;
    typedef typename ITraits::value_type               value_type;
    typedef CGAL::Kernel_traits<value_type>            KTraits;
    typedef typename KTraits::Kernel                   Kernel;

    internal::hilbert_sort_on_sphere(begin, end, Kernel(), policy,
				  static_cast<value_type *> (0), s);
}


  template <class RandomAccessIterator>
void hilbert_sort_on_sphere (RandomAccessIterator begin, RandomAccessIterator end, Hilbert_sort_middle_policy policy,
  const typename CGAL::Kernel_traits<typename std::iterator_traits<RandomAccessIterator>::value_type>::Kernel::Sphere_3 &s =
  typename CGAL::Kernel_traits<typename std::iterator_traits<RandomAccessIterator>::value_type>::Kernel::Sphere_3(
	typename CGAL::Kernel_traits<typename std::iterator_traits<RandomAccessIterator>::value_type>::Kernel::Point_3(
	typename CGAL::Kernel_traits<typename std::iterator_traits<RandomAccessIterator>::value_type>::Kernel::FT(0),
	typename CGAL::Kernel_traits<typename std::iterator_traits<RandomAccessIterator>::value_type>::Kernel::FT(0),
	typename CGAL::Kernel_traits<typename std::iterator_traits<RandomAccessIterator>::value_type>::Kernel::FT(0)
	), typename CGAL::Kernel_traits<typename std::iterator_traits<RandomAccessIterator>::value_type>::Kernel::FT(1)))
{
    typedef std::iterator_traits<RandomAccessIterator> ITraits;
    typedef typename ITraits::value_type               value_type;
    typedef CGAL::Kernel_traits<value_type>            KTraits;
    typedef typename KTraits::Kernel                   Kernel;

    internal::hilbert_sort_on_sphere(begin, end, Kernel(), policy,
				  static_cast<value_type *> (0), s);
}


  template <class RandomAccessIterator, class Kernel, class Policy>
void hilbert_sort_on_sphere (RandomAccessIterator begin, RandomAccessIterator end, const Kernel &k, Policy policy,
  const typename Kernel::Sphere_3 &s = typename Kernel::Sphere_3(
	typename Kernel::Point_3(typename Kernel::FT(0), typename Kernel::FT(0), typename Kernel::FT(0)), 
	typename Kernel::FT(1)))
{
    typedef std::iterator_traits<RandomAccessIterator> ITraits;
    typedef typename ITraits::value_type               value_type;

    internal::hilbert_sort_on_sphere(begin, end, 
			   k, policy, static_cast<value_type *> (0), s);
}

} // namespace CGAL

#endif//CGAL_HILBERT_SORT_H

