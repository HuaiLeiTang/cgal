// Copyright (c) 2006 Tel-Aviv University (Israel).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
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
//
// Author(s)     : Efi Fogel         <efif@post.tau.ac.il>

#ifndef CGAL_ARR_GREAT_CIRCULAR_ARC_ON_SPHERE_TRAITS_2_H
#define CGAL_ARR_GREAT_CIRCULAR_ARC_ON_SPHERE_TRAITS_2_H

// #define CGAL_ARR_PLANE

/*! \file
 * The traits-class that handles great circular arc on a spheres for the
 * arrangement on surface package.
 */

#include <CGAL/tags.h>
#include <CGAL/representation_tags.h>
#include <CGAL/intersections.h>
#if defined(CGAL_ARR_PLANE)
#include <CGAL/Arr_geometry_traits/Arr_plane_3.h>
#endif
#include <CGAL/Arr_enums.h>

#include <fstream>

CGAL_BEGIN_NAMESPACE

template <typename Kernel> class Arr_x_monotone_great_circular_arc_on_sphere_3;
template <typename Kernel> class Arr_great_circular_arc_on_sphere_3;
template <typename Kernel> class Arr_extended_direction_3;

/*! A traits class for maintaining an arrangement of spherical arcs */
template <typename T_Kernel>
class Arr_great_circular_arc_on_sphere_traits_2 : public T_Kernel {
  friend class Arr_x_monotone_great_circular_arc_on_sphere_3<T_Kernel>;
  friend class Arr_great_circular_arc_on_sphere_3<T_Kernel>;
  friend class Arr_extended_direction_3<T_Kernel>;

public:
  typedef T_Kernel                              Kernel;
  
  // Category tags:
  typedef Tag_true                              Has_left_category;
  typedef Tag_true                              Has_merge_category;
  typedef Tag_true                              Has_boundary_category;

  /*! Default constructor */
  Arr_great_circular_arc_on_sphere_traits_2(){}

protected:
  typedef typename Kernel::Direction_3          Direction_3;
  typedef typename Kernel::Vector_3             Vector_3;
  typedef typename Kernel::Ray_3                Ray_3;
  typedef typename Kernel::Line_3               Line_3;
#if defined(CGAL_ARR_PLANE)
  typedef Arr_plane_3<Kernel>                   Plane_3;
#else
  typedef typename Kernel::Plane_3              Plane_3;
#endif
  typedef typename Kernel::Point_3              Point_3;

  typedef typename Kernel::Direction_2          Direction_2;
  typedef typename Kernel::Vector_2             Vector_2;
  typedef typename Kernel::Ray_2                Ray_2;

  /*! Obtain the xy-plane
   * \return the xy-plane
   */
  inline static const Plane_3 & xy_plane()
  {
#if defined(CGAL_ARR_PLANE)
    static const Plane_3 p(0, 0, 1);
#else
    static const Plane_3 p(0, 0, 1, 0);
#endif
    return p;
  }

  /*! Obtain the yz-plane
   * \return the yz-plane
   */
  inline static const Plane_3 & yz_plane()
  {
#if defined(CGAL_ARR_PLANE)
    static const Plane_3 p(1, 0, 0);
#else
    static const Plane_3 p(1, 0, 0, 0);
#endif
    return p;
  }
  
  /*! Obtain the xz-plane
   * \return the xz-plane
   */
  inline static const Plane_3 & xz_plane()
  {
#if defined(CGAL_ARR_PLANE)
    static const Plane_3 p(0, -1, 0);
#else
    static const Plane_3 p(0, -1, 0, 0);
#endif
    return p;
  }
  
  /*! Obtain the possitive (north) pole
   * \return the possitive (north) pole
   */
  inline static const Direction_3 & pos_pole()
  {
    static const Direction_3 d(0, 0, 1);
    return d;
  }

  /*! Obtain the negative (south) pole
   * \return the negative (south) pole
   */
  inline static const Direction_3 & neg_pole()
  {
    static const Direction_3 d(0, 0, -1);
    return d;
  }

  /*! Obtain the 2D direction directed along the negative x axis
   * \return the direction directed at x = -infinity
   */
  inline static const Direction_2 & neg_x_2()
  {
    static const Direction_2 d(-1, 0);
    return d;
  }

  /*! Obtain the 2D direction directed along the positive y axis
   * \return the direction directed at y = +infinity
   */
  inline static const Direction_2 & pos_y_2()
  {
    static const Direction_2 d(0, 1);
    return d;
  }

  /*! Obtain the 2D direction directed along the negative y axis
   * \return the direction directed at y = -infinity
   */
  inline static const Direction_2 & neg_y_2()
  {
    static const Direction_2 d(0, -1);
    return d;
  }

  /*! Is a given direction colinear with the x-axis?
   * \param d the direction
   * \return true iff d is directed towards the positive or negative x axis
   */
  inline static bool is_colinear_x(Direction_2 d)
  { return (CGAL::sign(d.dy()) == ZERO); }

  inline static bool is_x_positive(Direction_2 d)
  { return (CGAL::sign(d.dx()) == POSITIVE); }

  inline static bool is_x_negative(Direction_2 d)
  { return (CGAL::sign(d.dx()) == NEGATIVE); }

  inline static Sign x_sign(Direction_3 d) { return CGAL::sign(d.dx()); }

  inline static Sign y_sign(Direction_3 d) { return CGAL::sign(d.dy()); }  

  inline static Sign z_sign(Direction_3 d) { return CGAL::sign(d.dz()); }
  
  typedef Direction_2 (*Project)(const Direction_3 & d) ;
  
  /*! Project a 3D direction onto the xy-plane
   * \todo kernel is missing: ConstructVector_3::operator()(Direction_3 d)
   * \param d the 3D direction
   * \return the projection onto the xy-plane
   */
  inline static Direction_2 project_xy(const Direction_3 & d)
  {
    Direction_2 dir(d.dx(), d.dy());
    return dir;
  }
  
  /*! Project a 3D direction onto the yz-plane
   * \todo kernel is missing: ConstructVector_3::operator()(Direction_3 d)
   * \param d the 3D direction
   * \return the projection onto the yz-plane
   */
  inline static Direction_2 project_yz(const Direction_3 & d)
  {
    Direction_2 dir(d.dy(), d.dz());
    return dir;
  }
  
  /*! Project a 3D direction onto the zx-plane
   * \todo kernel is missing: ConstructVector_3::operator()(Direction_3 d)
   * \param d the 3D direction
   * \return the projection onto the xz-plane
   */
  inline static Direction_2 project_xz(const Direction_3 & d)
  {
    Direction_2 dir(d.dx(), d.dz());
    return dir;
  }

  /*! Compare the relative position of a direction and a plane.
   * \param plane the plane.
   * \param dir the direction.
   */
  inline Oriented_side oriented_side(const Plane_3 & plane,
                                     const Direction_3 dir) const
  {
    const Kernel * kernel = this;
    Ray_3 ray = kernel->construct_ray_3_object()(ORIGIN, dir);
    Vector_3 vec = kernel->construct_vector_3_object()(ray);
    Point_3 point = kernel->construct_translated_point_3_object()(ORIGIN, vec);
    return plane.oriented_side(point);
  }
  
  /*! Compute the orientation of two directions.
   * \param d1 the first direction.
   * \param d2 the second direction.
   * \return the relative orientation of d1 and d2. 
   */
  static inline Orientation orientation(const Direction_2 & d1,
                                        const Direction_2 & d2)
  {
    Kernel kernel;
    Ray_2 r1 = kernel.construct_ray_2_object()(ORIGIN, d1);
    Vector_2 v1 = kernel.construct_vector_2_object()(r1);
    Ray_2 r2 = kernel.construct_ray_2_object()(ORIGIN, d2);
    Vector_2 v2 = kernel.construct_vector_2_object()(r2);
    return kernel.orientation_2_object()(v1, v2);
  }

  /*! Compare two endpoint directions by y.
   * \param p1 the first enpoint direction.
   * \param p2 the second endpoint direction.
   * \param d1_xy the projection of the first endpoint onto the xy-plane.
   * \return SMALLER - x(p1) < x(p2);
   *         SMALLER - x(p1) = x(p2) and y(p1) < y(p2);
   *         EQUAL   - x(p1) = x(p2) and y(p1) = y(p2);
   *         LARGER  - x(p1) = x(p2) and y(p1) > y(p2);
   *         LARGER  - x(p1) > x(p2).
   */
  static inline Comparison_result compare_y(const Direction_3 & d1,
                                            const Direction_3 & d2)
  {
    typedef typename Kernel::FT                     FT;
    typedef typename Kernel::Construct_vector_3     Construct_vector_3;
    Kernel kernel;
    Construct_vector_3 construct_vec_3 = kernel.construct_vector_3_object();
    Vector_3 v1 = construct_vec_3(d1);
    Vector_3 v2 = construct_vec_3(d2);

    FT norm1 = v1 * v1;
    FT norm2 = v2 * v2;

    FT dot_p1 = v1.z();
    FT dot_p2 = v2.z();
    
    return CGAL::compare(CGAL::sign(dot_p1) * dot_p1 * dot_p1 * norm2,
                         CGAL::sign(dot_p2) * dot_p2 * dot_p2 * norm1);
  }

  /*! Compare two endpoint directions by x.
   * \param p1 the first enpoint direction.
   * \param p2 the second endpoint direction.
   * \param d1_xy the projection of the first endpoint onto the xy-plane.
   * \return SMALLER - x(p1) < x(p2);
   *         SMALLER - x(p1) = x(p2) and y(p1) < y(p2);
   *         EQUAL   - x(p1) = x(p2) and y(p1) = y(p2);
   *         LARGER  - x(p1) = x(p2) and y(p1) > y(p2);
   *         LARGER  - x(p1) > x(p2).
   * \pre d1 does not lie on the closed discontinuity arc.
   * \pre d2 does not lie on the closed discontinuity arc.
   */
  inline Comparison_result compare_x(const Direction_3 & d1,
                                     const Direction_3 & d2) const
  {
    // Compare the projections onto the xy plane:
    Direction_2 d1_2 = project_xy(d1);
    Direction_2 d2_2 = project_xy(d2);

    if (Kernel::equal_2_object()(d1_2, d2_2)) return EQUAL;
    
    const Direction_2 & nx = neg_x_2();
    return (Kernel::counterclockwise_in_between_2_object()(nx, d1_2, d2_2)) ?
      LARGER : SMALLER;
  }


  /*! Compare two endpoint directions lexigoraphically: by x, then by y.
   * \param p1 the first enpoint direction.
   * \param p2 the second endpoint direction.
   * \return SMALLER - x(p1) < x(p2);
   *         SMALLER - x(p1) = x(p2) and y(p1) < y(p2);
   *         EQUAL   - x(p1) = x(p2) and y(p1) = y(p2);
   *         LARGER  - x(p1) = x(p2) and y(p1) > y(p2);
   *         LARGER  - x(p1) > x(p2).
   * \pre d1 does not lie on the discontinuity arc.
   * \pre d2 does not lie on the discontinuity arc.
   */
  inline Comparison_result compare_xy(const Direction_3 & d1,
                                      const Direction_3 & d2) const
  {
    Comparison_result res = compare_x(d1, d2);
    if (res == EQUAL) return compare_y(d1, d2);
    return res;
  }
  
public:
  // Traits objects
  typedef Arr_extended_direction_3<Kernel>              Point_2;
  typedef Arr_x_monotone_great_circular_arc_on_sphere_3<Kernel>
                                                        X_monotone_curve_2;
  typedef Arr_great_circular_arc_on_sphere_3<Kernel>    Curve_2;
  typedef unsigned int                                  Multiplicity;

public:
  /// \name Basic functor definitions
  //@{

  class Compare_x_2 {
  protected:
    typedef Arr_great_circular_arc_on_sphere_traits_2<Kernel> Traits;

    /*! The traits (in case it has state) */
    const Traits * m_traits;
    
    /*! Constructor
     * \param traits the traits (in case it has state)
     */
    Compare_x_2(const Traits * traits) : m_traits(traits) {}

    friend class Arr_great_circular_arc_on_sphere_traits_2<Kernel>;
    
  public:    
    /*! Compare the x-coordinates of two endpoint directions.
     * \param p1 the first endpoint direction.
     * \param p2 the second endpoint direction.
     * \return SMALLER - x(p1) < x(p2);
     *         EQUAL   - x(p1) = x(p2);
     *         LARGER  - x(p1) > x(p2).
     * \pre p1 does not lie on the closed discontinuity arc.
     * \pre p2 does not lie on the closed discontinuity arc.
     */
    Comparison_result operator()(const Point_2 & p1, const Point_2 & p2) const
    {
      CGAL_precondition(p1.is_no_boundary());
      CGAL_precondition(p2.is_no_boundary());

      return m_traits->compare_x(p1, p2);
    }

    /*! Compare the x-coordinates of a point direction and an endpoint
     * of a spherical arc.
     * A spherical arc that coincides with the discontinuity arc is vertical,
     * and considered to have the smallest x-coordinate. Thus, if the given
     * sphercial arc does coincide with the discontinuity arc, the point is
     * larger.
     * \param p the endpoint direction.
     * \param xc the curve, the endpoint of which is compared.
     * \param ind MIN_END - the minimal end of xc or
     *            MAX_END - the maximal end of xc.
     * \return SMALLER - x(p) < x(xc, ind);
     *         EQUAL   - x(p) = x(xc, ind);
     *         LARGER  - x(p) > x(xc, ind).
     * \pre p is not on the closed discontinuity arc.
     * \pre the endpoint indicated by xv and ind is on the discontinuity arc.
     */
    Comparison_result operator()(const Point_2 & p,
                                 const X_monotone_curve_2 & xc,
                                 Curve_end ind) const
    {
      typedef Arr_great_circular_arc_on_sphere_traits_2<Kernel> Traits;

      CGAL_precondition(p.is_no_boundary());
      CGAL_precondition_code
        (const Point_2 & p2 = (ind == MIN_END) ? xc.left() : xc.right(););
      CGAL_precondition(!p2.is_no_boundary());

      if (xc.is_vertical()) {
        // If xc coincides with the discontinuity arc, all its points are
        // assumed to be smaller than non-boundary points:
        if (xc.is_on_boundary()) return LARGER;
        // xc is vertical, but does not coincide with the discontinuity arc,
        // obtain the other endpoint:
        const Point_2 & q = (ind == MIN_END) ? xc.right() : xc.left();
        Direction_2 p_2 = Traits::project_xy(p);
        Direction_2 q_2 = Traits::project_xy(q);
        const Kernel * kernel = m_traits;
        if (kernel->equal_2_object()(p_2, q_2)) return EQUAL;
        const Direction_2 & nx = Traits::neg_x_2();
        return (kernel->counterclockwise_in_between_2_object()(nx, p_2, q_2)) ?
          LARGER : SMALLER;
      }

      // xc is not a vertical sphercial_arc:
      return (ind == MIN_END) ? LARGER : SMALLER;
    }

    /*! Compare the x-coordinates of two endpoint directions.
     * \param p the endpoint direction.
     * \param xc1 the first curve, the endpoint of which is compared.
     * \param ind1 MIN_END - the minimal end of xc1 or
     *             MAX_END - the maximal end of xc1.
     * \param xc2 the second curve, the endpoint of which is compared.
     * \param ind2 MIN_END - the minimal end of xc2 or
     *             MAX_END - the maximal end of xc2.
     * \return SMALLER - x(xc1, ind1) < x(xc2, ind2);
     *         EQUAL   - x(xc1, ind1) = x(xc2, ind2);
     *         LARGER  - x(xc1, ind1) > x(xc2, ind2).
     * \pre the endpoint indicated by xv1 and ind1 is on the discontinuity arc.
     * \pre the endpoint indicated by xv2 and ind2 is on the discontinuity arc.
     */
    Comparison_result operator()(const X_monotone_curve_2 & xc1,
                                 Curve_end ind1,
                                 const X_monotone_curve_2 & xc2,
                                 Curve_end ind2) const
    {
      typedef Arr_great_circular_arc_on_sphere_traits_2<Kernel> Traits;

      CGAL_precondition_code
        (const Point_2 & p1 = (ind1 == MIN_END) ? xc1.left() : xc1.right(););
      CGAL_precondition(!p1.is_no_boundary());
      CGAL_precondition_code
        (const Point_2 & p2 = (ind2 == MIN_END) ? xc2.left() : xc2.right(););
      CGAL_precondition(!p2.is_no_boundary());

      if (xc1.is_vertical() && xc2.is_vertical()) {
        if (xc1.is_on_boundary() && xc2.is_on_boundary()) return EQUAL;
        if (xc1.is_on_boundary()) return SMALLER;
        if (xc2.is_on_boundary()) return LARGER;
        // Non of the arcs coincide with the discontinuity arc:
        // x(xc1, ind) <= x(xc1, !ind)
        // x(xc2, ind) <= x(xc2, !ind)
        const Point_2 & p = (ind1 == MIN_END) ? xc1.right() : xc1.left();
        const Point_2 & q = (ind2 == MIN_END) ? xc2.right() : xc2.left();
        Direction_2 p_2 = Traits::project_xy(p);
        Direction_2 q_2 = Traits::project_xy(q);
        const Kernel * kernel = m_traits;
        if (kernel->equal_2_object()(p_2, q_2)) return EQUAL;
        const Direction_2 & nx = Traits::neg_x_2();
        return (kernel->counterclockwise_in_between_2_object()(nx, p_2, q_2)) ?
          LARGER : SMALLER;
      }
      if (xc1.is_vertical()) {
        if (xc1.is_on_boundary()) return SMALLER;
        return (ind2 == MAX_END) ? SMALLER : LARGER;
      }
      if (xc2.is_vertical()) {
        if (xc2.is_on_boundary()) return LARGER;
        return (ind1 == MAX_END) ? LARGER : SMALLER;
      }
      // Non of the arcs are vertical:
      if (ind1 == ind2) return EQUAL;
      if (ind1 == MIN_END) return SMALLER;
      return LARGER;
    }
  };

  /*! Obtain a Compare_x_2 function object */
  Compare_x_2 compare_x_2_object() const { return Compare_x_2(this); }

  class Compare_xy_2 {
  protected:
    typedef Arr_great_circular_arc_on_sphere_traits_2<Kernel> Traits;

    /*! The traits (in case it has state) */
    const Traits * m_traits;
    
    /*! Constructor
     * \param traits the traits (in case it has state)
     */
    Compare_xy_2(const Traits * traits) : m_traits(traits) {}

    friend class Arr_great_circular_arc_on_sphere_traits_2<Kernel>;
    
  public:
    /*! Compare two endpoint directions lexigoraphically: by x, then by y.
     * \param p1 the first enpoint direction.
     * \param p2 the second endpoint direction.
     * \return SMALLER - x(p1) < x(p2);
     *         SMALLER - x(p1) = x(p2) and y(p1) < y(p2);
     *         EQUAL   - x(p1) = x(p2) and y(p1) = y(p2);
     *         LARGER  - x(p1) = x(p2) and y(p1) > y(p2);
     *         LARGER  - x(p1) > x(p2).
     * \pre p1 is not on the discontinuity arc.
     * \pre p2 is not on the discontinuity arc.
     */
    Comparison_result operator()(const Point_2 & p1, const Point_2 & p2) const
    {
      typedef Arr_great_circular_arc_on_sphere_traits_2<Kernel> Traits;

      CGAL_precondition(p1.is_no_boundary());
      CGAL_precondition(p2.is_no_boundary());
      
      return m_traits->compare_xy(p1, p2);
    }
  };

  /*! Obtain a Compare_xy_2 function object */
  Compare_xy_2 compare_xy_2_object() const { return Compare_xy_2(this); }

  class Boundary_in_x_2 {
  public:
    /*! Determine whether an endpoint of an x-monotone curve lies on an
     * x-boundary.
     * Note that if the curve end coincides with a pole, then unless the curve
     * coincides with discontinuity arc, the curve end is considered not to be
     * on a boundary. If the curve coincides with discontinuity arc, it is
     * assumed to be smaller than any other object.
     * \param xc the curve.
     * \param ind MIN_END - the minimal end of xc or
     *            MAX_END - the maximal end of xc.
     * \return
     *   AFTER_DISCONTINUITY  - the curve end is on the open discontinuity arc 
     *                          and it is the left endpoint
     *   NO_BOUNDARY          - the curve end does not lie on the open
     *                          discontinuity arc.
     *   BEFORE_DISCONTINUITY - the curve end is on the open discontinuity arc
     *                          and it is the right endpoint
     */
    Boundary_type operator()(const X_monotone_curve_2 & xc,
                             Curve_end ind) const
    {
      if (xc.is_vertical()) {
        if (xc.is_on_boundary()) return AFTER_DISCONTINUITY;
        return NO_BOUNDARY;
      }

      return (ind == MIN_END) ?
        // Process left:
        ((xc.left().is_no_boundary()) ? NO_BOUNDARY : AFTER_DISCONTINUITY) :

        // ind == MAX_END => process left():
        ((xc.right().is_no_boundary()) ? NO_BOUNDARY : BEFORE_DISCONTINUITY);
    }
  };

  /*! Obtain an Boundary_in_x_2 functor object. */
  Boundary_in_x_2 boundary_in_x_2_object() const { return Boundary_in_x_2(); }

  class Boundary_in_y_2 {
  public:
    /*! Determine whether an end of an x-monotone curve lies on a y-boundary.
     * \param xc the curve.
     * \param ind MIN_END - the minimal end of xc or
     *            MAX_END - the maximal end of xc.
     * \return
     *   the curve end is on the boundary and
     *     is the right endpoint                    => AFTER_SINGULARITY, else
     *   the curve end does not lie on the boundary => NO_BOUNDARY, 
     *   the curve end is on the boundary and
     *     is the left endpoint                     => BEFORE_SINGULARITY.
     */
    Boundary_type operator()(const X_monotone_curve_2 & xc,
                             Curve_end ind) const
    {
      return (ind == MIN_END) ?
        ((xc.left().is_min_boundary()) ? AFTER_SINGULARITY : NO_BOUNDARY) :

        // ind == MAX_END
        ((xc.right().is_max_boundary()) ? BEFORE_SINGULARITY : NO_BOUNDARY);
    }
  };

  /*! Obtain an Boundary_in_x_2 functor object. */
  Boundary_in_y_2 boundary_in_y_2_object() const { return Boundary_in_y_2(); }
    
  class Construct_min_vertex_2 {
  public:
    /*! Get the left endpoint of the x-monotone curve (spherical_arc).
     * \param xc the curve.
     * \return the left endpoint.
     */
    const Point_2 & operator()(const X_monotone_curve_2 & xc) const
    { return xc.left(); }
  };

  /*! Obtain a Construct_min_vertex_2 function object */
  Construct_min_vertex_2 construct_min_vertex_2_object() const
  { return Construct_min_vertex_2(); }

  class Construct_max_vertex_2 {
  public:
    /*! Get the right endpoint of the x-monotone curve(spherical_arc).
     * \param xc the curve.
     * \return the right endpoint.
     */
    const Point_2 & operator()(const X_monotone_curve_2 & xc) const
    { return xc.right(); }
  };

  /*! Obtain a Construct_max_vertex_2 function object */
  Construct_max_vertex_2 construct_max_vertex_2_object() const
  { return Construct_max_vertex_2(); }

  class Is_vertical_2 {
  public:
    /*! Check whether the given x-monotone curve is a vertical spherical_arc.
     * \param xc the curve.
     * \return true if the curve is a vertical spherical_arc; false otherwise.
     */
    bool operator()(const X_monotone_curve_2 & xc) const
    {
      CGAL_precondition(!xc.is_degenerate());
      return xc.is_vertical();
    }
  };

  /*! Obtain an Is_vertical_2 function object */
  Is_vertical_2 is_vertical_2_object() const { return Is_vertical_2(); }

  class Compare_y_at_x_2 {
  protected:
    typedef Arr_great_circular_arc_on_sphere_traits_2<Kernel> Traits;

    /*! The traits (in case it has state) */
    const Traits * m_traits;
    
    /*! Constructor
     * \param traits the traits (in case it has state)
     */
    Compare_y_at_x_2(const Traits * traits) : m_traits(traits) {}

    friend class Arr_great_circular_arc_on_sphere_traits_2<Kernel>;
    
  public:
    /*! Return the location of the given point with respect to the input curve.
     * \param xc the curve.
     * \param p the point.
     * \return SMALLER - y(p) < xc(x(p)), i.e. the point is below the curve;
     *         EQUAL   - p lies on the curve.
     *         LARGER  - y(p) > xc(x(p)), i.e. the point is above the curve;
     * \pre p is not a singularity point.
     * \pre p is in the x-range of xc.
     */
    Comparison_result operator()(const Point_2 & p,
                                 const X_monotone_curve_2 & xc) const
    {
      typedef Arr_great_circular_arc_on_sphere_traits_2<Kernel> Traits;

      CGAL_precondition(!xc.is_degenerate());
      CGAL_precondition(!p.is_min_boundary() && !p.is_max_boundary());
      CGAL_precondition(xc.is_in_x_range(p));

      if (xc.is_vertical()) {
        // Compare the point with the left endpoint. If smaller, return SMALLER.
        // Otherwise, if EQUAL, return EQUAL.
        // Otherwise, compare with the right endpoint. If larger, return LARGER.
        // Otherwise, return EQUAL:
        if (!xc.left().is_min_boundary()) {
          Comparison_result cr = m_traits->compare_y(p, xc.left());
          if (cr != LARGER) return cr;
        }
        if (xc.right().is_max_boundary()) return EQUAL;
        Comparison_result cr = m_traits->compare_y(p, xc.right());
        return (cr == LARGER) ? LARGER : EQUAL;
      }

      // Compare the point to the underlying plane of xc:
      Oriented_side os = m_traits->oriented_side(xc.plane(), p);
      return (os == ON_ORIENTED_BOUNDARY) ? EQUAL :
        (xc.is_directed_right()) ?
        ((os == ON_NEGATIVE_SIDE) ? SMALLER : LARGER) : 
        ((os == ON_NEGATIVE_SIDE) ? LARGER : SMALLER);
    }

    /*! Compare the relative y-positions of two curves at an x-boundary.
     * \param xc1 the first curve.
     * \param xc2 the second curve.
     * \param ind MIN_END - the minimal end of xc or
     *            MAX_END - the maximal end of xc.
     * \return SMALLER - xc1 lies below xc2;
     *         EQUAL   - xc1 and xc2 overlap;
     *         LARGER  - xc1 lies above xc2;
     * \pre the endpoint indicated by xv1 and ind1 is on the discontinuity arc.
     * \pre the endpoint indicated by xv2 and ind2 is on the discontinuity arc.
     */
    Comparison_result operator()(const X_monotone_curve_2 & xc1,
                                 Curve_end ind1,
                                 const X_monotone_curve_2 & xc2, 
                                 Curve_end ind2) const
    {
      typedef Arr_great_circular_arc_on_sphere_traits_2<Kernel> Traits;

      CGAL_precondition(!xc1.is_degenerate());
      CGAL_precondition(!xc2.is_degenerate());

      const Point_2 & p1 = (ind1 == MIN_END) ? xc1.left() : xc1.right();
      const Point_2 & p2 = (ind2 == MIN_END) ? xc2.left() : xc2.right();
      CGAL_precondition(!p1.is_no_boundary());
      CGAL_precondition(!p2.is_no_boundary());
      
      Direction_2 p1_2 = project_xz(p1);
      Direction_2 p2_2 = project_xz(p2);
      Orientation orient = m_traits->orientation(p1_2, p2_2);

      return (orient == RIGHT_TURN) ? SMALLER :
        (orient == COLLINEAR) ? EQUAL : LARGER;
    }

    /*! Compare the relative y-positions of two curves at an x-boundary.
     * \param xc1 the first curve.
     * \param xc2 the second curve.
     * \param ind MIN_END - the minimal end of xc or
     *            MAX_END - the maximal end of xc.
     * \return SMALLER - xc1 lies below xc2;
     *         EQUAL   - xc1 and xc2 overlap;
     *         LARGER  - xc1 lies above xc2;
     * \pre If xc1 is vertical, xc1 coincides with the discontinuity arc.
     * Otherwise, the endpoint indicated by xc1 and ind is on the discontinuity
     * open arc.
     * \pre If xc2 is vertical, xc2 coincides with the discontinuity arc.
     * Otherwise, the endpoint indicated by xc2 and ind is on the discontinuity
     * open arc.
     */
    Comparison_result operator()(const X_monotone_curve_2 & xc1,
                                 const X_monotone_curve_2 & xc2, 
                                 Curve_end ind) const
    {
      typedef Arr_great_circular_arc_on_sphere_traits_2<Kernel> Traits;

      CGAL_precondition(!xc1.is_degenerate());
      CGAL_precondition(!xc2.is_degenerate());

      const Point_2 & l1 = xc1.left();
      const Point_2 & r1 = xc1.right();
      const Point_2 & l2 = xc2.left();
      const Point_2 & r2 = xc2.right();

      // If xc1 is vertical, xc1 coincides with the discontinuity arc:
      if (xc1.is_vertical()) {
        CGAL_precondition(!l1.is_no_boundary());
        CGAL_precondition(!r1.is_no_boundary());
      }

      // If xc2 is vertical, xc2 coincides with the discontinuity arc:
      if (xc2.is_vertical()) {
        CGAL_precondition(!l2.is_no_boundary());
        CGAL_precondition(!r2.is_no_boundary());
      }

      if (ind == MIN_END) {
        // Handle the south pole. It has the smallest y coords:
        if (l1.is_min_boundary())
          return (l2.is_min_boundary()) ? EQUAL : SMALLER;
        if (l2.is_min_boundary()) return LARGER;

        // None of xc1 and xc2 endpoints coincide with a pole:
        Comparison_result cr = m_traits->compare_y(l1, l2);
        if (cr != EQUAL) return cr;

        // If Both arcs are vertical, they overlap:
        if (xc1.is_vertical() && xc2.is_vertical()) return EQUAL;
        if (xc1.is_vertical()) return LARGER;
        if (xc2.is_vertical()) return SMALLER;

        // Non of the arcs is verticel. Thus, non of the endpoints coincide
        // with a pole.
        // Compare the y-coord. at the x-coord of the most left right-endpoint.
        CGAL_assertion(r1.is_no_boundary());
        CGAL_assertion(r2.is_no_boundary());
        
        if (m_traits->compare_xy(r1, r2) == LARGER) {
          // use r2 and xc1:
          Oriented_side os = m_traits->oriented_side(xc1.plane(), r2);
          return (os == ON_ORIENTED_BOUNDARY) ? EQUAL :
            (xc1.is_directed_right()) ?
            ((os == ON_NEGATIVE_SIDE) ? LARGER : SMALLER) : 
            ((os == ON_NEGATIVE_SIDE) ? SMALLER : LARGER);
        }
        // use r1 and xc2: 
        Oriented_side os = m_traits->oriented_side(xc2.plane(), r1);
        return (os == ON_ORIENTED_BOUNDARY) ? EQUAL :
          (xc2.is_directed_right()) ?
          ((os == ON_NEGATIVE_SIDE) ? SMALLER : LARGER) : 
          ((os == ON_NEGATIVE_SIDE) ? LARGER : SMALLER);
      }

      // ind == MAX_END
      
      // Handle the north pole. It has the largest y coords:
      if (r1.is_max_boundary()) return (r2.is_max_boundary()) ? EQUAL : LARGER;
      if (r2.is_max_boundary()) return SMALLER;

      // None of xc1 and xc2 endpoints coincide with a pole:
      Direction_2 r1_xy = m_traits->project_xy(r1);
      Comparison_result cr = m_traits->compare_y(r1, r2);
      if (cr != EQUAL) return cr;

      // If Both arcs are vertical, they overlap:
      if (xc1.is_vertical() && xc2.is_vertical()) return EQUAL;
      if (xc1.is_vertical()) return LARGER;
      if (xc2.is_vertical()) return SMALLER;
        
      // Compare to the left:
      Direction_2 p_r1 = m_traits->project_xy(r1);
      cr = m_traits->compare_y(r1, r2);
      if (cr != EQUAL) return cr;

      // Non of the arcs is verticel. Thus, non of the endpoints coincide with
      // a pole.
      // Compare the y-coord. at the x-coord of the most right left-endpoint.
      CGAL_assertion(l1.is_no_boundary());
      CGAL_assertion(l2.is_no_boundary());

      if (m_traits->compare_xy(l1, l2) == SMALLER) {
        // use l2 and xc1:
        Oriented_side os = m_traits->oriented_side(xc1.plane(), l2);
        return (os == ON_ORIENTED_BOUNDARY) ? EQUAL :
          (xc1.is_directed_right()) ?
          ((os == ON_NEGATIVE_SIDE) ? LARGER : SMALLER) : 
          ((os == ON_NEGATIVE_SIDE) ? SMALLER : LARGER);
      }
      // use l1 and xc2: 
      Oriented_side os = m_traits->oriented_side(xc2.plane(), l1);
      return (os == ON_ORIENTED_BOUNDARY) ? EQUAL :
        (xc2.is_directed_right()) ?
        ((os == ON_NEGATIVE_SIDE) ? SMALLER : LARGER) : 
        ((os == ON_NEGATIVE_SIDE) ? LARGER : SMALLER);
    }
  };

  /*! Obtain a Compare_y_at_x_2 function object */
  Compare_y_at_x_2 compare_y_at_x_2_object() const
  { return Compare_y_at_x_2(this); }

  class Compare_y_at_x_left_2 {
  protected:
    typedef Arr_great_circular_arc_on_sphere_traits_2<Kernel> Traits;

    /*! The traits (in case it has state) */
    const Traits * m_traits;
    
    /*! Constructor
     * \param traits the traits (in case it has state)
     */
    Compare_y_at_x_left_2(const Traits * traits) : m_traits(traits) {}

    friend class Arr_great_circular_arc_on_sphere_traits_2<Kernel>;
    
  public:
    /*! Compare the y value of two x-monotone curves immediately to the left
     * of their intersection point.
     * \param xc1 the first curve.
     * \param xc2 the second curve.
     * \param p the intersection point.
     * \return the relative position of xc1 with respect to xc2 immdiately to
     *         the left of p: SMALLER, EQUAL, or LARGER.
     * \pre the point p lies on both curves, and both of them must be also be
     *      defined (lexicographically) to its left.
     */
    Comparison_result operator()(const X_monotone_curve_2 & xc1,
                                 const X_monotone_curve_2 & xc2,
                                 const Point_2 & p) const
    {
      CGAL_precondition(!xc1.is_degenerate());
      CGAL_precondition(!xc2.is_degenerate());
      CGAL_precondition(p == xc1.right());
      CGAL_precondition(p == xc2.right());

      // If Both arcs are vertical, they overlap:
      if (xc1.is_vertical() && xc2.is_vertical()) return EQUAL;
      if (xc1.is_vertical()) return SMALLER;
      if (xc2.is_vertical()) return LARGER;

      // Non of the arc is verticel. Thus, non of the endpoints coincide with
      // a pole.
      // Compare the y-coord. at the x-coord of the most right left-endpoint.
      const Point_2 & l1 = xc1.left();
      const Point_2 & l2 = xc2.left();
      if (!l1.is_no_boundary()) {
        // use l2 and xc1:
        Oriented_side os = m_traits->oriented_side(xc1.plane(), l2);
        return (os == ON_ORIENTED_BOUNDARY) ? EQUAL :
          (xc1.is_directed_right()) ?
          ((os == ON_NEGATIVE_SIDE) ? LARGER : SMALLER) : 
          ((os == ON_NEGATIVE_SIDE) ? SMALLER : LARGER);
      }
      if (!l2.is_no_boundary()) {
        // use l1 and xc2:
        Oriented_side os = m_traits->oriented_side(xc2.plane(), l1);
        return (os == ON_ORIENTED_BOUNDARY) ? EQUAL :
          (xc2.is_directed_right()) ?
          ((os == ON_NEGATIVE_SIDE) ? SMALLER : LARGER) : 
          ((os == ON_NEGATIVE_SIDE) ? LARGER : SMALLER);
      }

      if (m_traits->compare_xy(l1, l2) == SMALLER) {
        // use l2 and xc1:
        Oriented_side os = m_traits->oriented_side(xc1.plane(), l2);
        return (os == ON_ORIENTED_BOUNDARY) ? EQUAL :
          (xc1.is_directed_right()) ?
          ((os == ON_NEGATIVE_SIDE) ? LARGER : SMALLER) : 
          ((os == ON_NEGATIVE_SIDE) ? SMALLER : LARGER);
      }
      // use l1 and xc2: 
      Oriented_side os = m_traits->oriented_side(xc2.plane(), l1);
      return (os == ON_ORIENTED_BOUNDARY) ? EQUAL :
        (xc2.is_directed_right()) ?
        ((os == ON_NEGATIVE_SIDE) ? SMALLER : LARGER) : 
        ((os == ON_NEGATIVE_SIDE) ? LARGER : SMALLER);
    }
  };

  /*! Obtain a Compare_y_at_x_left_2 function object */
  Compare_y_at_x_left_2 compare_y_at_x_left_2_object() const
  { return Compare_y_at_x_left_2(this); }
  
  class Compare_y_at_x_right_2 {
  protected:
    typedef Arr_great_circular_arc_on_sphere_traits_2<Kernel> Traits;

    /*! The traits (in case it has state) */
    const Traits * m_traits;
    
    /*! Constructor
     * \param traits the traits (in case it has state)
     */
    Compare_y_at_x_right_2(const Traits * traits) : m_traits(traits) {}

    friend class Arr_great_circular_arc_on_sphere_traits_2<Kernel>;
    
  public:
    /*! Compare the y value of two x-monotone curves immediately to the right
     * of their intersection point.
     * \param xc1 the first curve.
     * \param xc2 the second curve.
     * \param p the intersection point.
     * \return the relative position of xc1 with respect to xc2 immdiately to
     *         the right of p: SMALLER, EQUAL, or LARGER.
     * \pre the point p lies on both curves, and both of them must also be
     *      defined to its right (lexicographically).
     */
    Comparison_result operator()(const X_monotone_curve_2 & xc1,
                                 const X_monotone_curve_2 & xc2,
                                 const Point_2 &) const
    {
      CGAL_precondition(!xc1.is_degenerate());
      CGAL_precondition(!xc2.is_degenerate());

      // CGAL_precondition(p == xc1.left());
      // CGAL_precondition(p == xc2.left());

      // If Both arcs are vertical, they overlap:
      if (xc1.is_vertical() && xc2.is_vertical()) return EQUAL;
      if (xc1.is_vertical()) return LARGER;
      if (xc2.is_vertical()) return SMALLER;

      // Non of the arcs is verticel. Thus, non of the endpoints coincide with
      // a pole.
      // Compare the y-coord. at the x-coord of the most left right-endpoint.
      const Point_2 & r1 = xc1.right();
      const Point_2 & r2 = xc2.right();
      if (!r1.is_no_boundary()) {
        // use r2 and xc1:
        Oriented_side os = m_traits->oriented_side(xc1.plane(), r2);
        return (os == ON_ORIENTED_BOUNDARY) ? EQUAL :
          (xc1.is_directed_right()) ?
          ((os == ON_NEGATIVE_SIDE) ? LARGER : SMALLER) : 
          ((os == ON_NEGATIVE_SIDE) ? SMALLER : LARGER);
      }
      if (!r2.is_no_boundary()) {
        // use r1 and xc2:
        Oriented_side os = m_traits->oriented_side(xc2.plane(), r1);
        return (os == ON_ORIENTED_BOUNDARY) ? EQUAL :
          (xc2.is_directed_right()) ?
          ((os == ON_NEGATIVE_SIDE) ? SMALLER : LARGER) : 
          ((os == ON_NEGATIVE_SIDE) ? LARGER : SMALLER);
      }
      if (m_traits->compare_xy(r1, r2) == LARGER) {
        // use r2 and xc1:
        Oriented_side os = m_traits->oriented_side(xc1.plane(), r2);
        return (os == ON_ORIENTED_BOUNDARY) ? EQUAL :
          (xc1.is_directed_right()) ?
          ((os == ON_NEGATIVE_SIDE) ? LARGER : SMALLER) : 
          ((os == ON_NEGATIVE_SIDE) ? SMALLER : LARGER);
      }
      // use r1 and xc2: 
      Oriented_side os = m_traits->oriented_side(xc2.plane(), r1);
      return (os == ON_ORIENTED_BOUNDARY) ? EQUAL :
        (xc2.is_directed_right()) ?
        ((os == ON_NEGATIVE_SIDE) ? SMALLER : LARGER) : 
        ((os == ON_NEGATIVE_SIDE) ? LARGER : SMALLER);
    }
  };

  /*! Obtain a Compare_y_at_x_right_2 function object */
  Compare_y_at_x_right_2 compare_y_at_x_right_2_object() const
  { return Compare_y_at_x_right_2(this); }

  class Equal_2 {
  protected:
    typedef Arr_great_circular_arc_on_sphere_traits_2<Kernel> Traits;

    /*! The traits (in case it has state) */
    const Traits * m_traits;
    
    /*! Constructor
     * \param traits the traits (in case it has state)
     */
    Equal_2(const Traits * traits) : m_traits(traits) {}

    friend class Arr_great_circular_arc_on_sphere_traits_2<Kernel>;
    
  public:
    /*! Determines whether the two x-monotone curves are the same (have the
     * same graph).
     * \param xc1 the first curve.
     * \param xc2 the second curve.
     * \return true if the two curves are the same; false otherwise.
     */
    bool operator()(const X_monotone_curve_2 & xc1,
                    const X_monotone_curve_2 & xc2) const
    {
      CGAL_precondition(!xc1.is_degenerate());
      CGAL_precondition(!xc2.is_degenerate());

      const Kernel * kernel = m_traits;
      typename Kernel::Equal_3 equal_3 = kernel->equal_3_object();
      return ((equal_3(xc1.left(), xc2.left()) &&
               equal_3(xc1.right(), xc2.right()) &&
               equal_3(xc1.plane(), xc2.plane())) ||
              (equal_3(xc1.left(), xc2.right()) &&
               equal_3(xc1.right(), xc2.left()) &&
               equal_3(xc1.plane(), xc2.plane().opposite())));
    }

    /*! Determines whether the two points are the same.
     * \param p1 the first point.
     * \param p2 the second point.
     * \return true if the two point are the same; false otherwise.
     */
    bool operator()(const Point_2 & p1, const Point_2 & p2) const
    {
      const Kernel * kernel = m_traits;
      return kernel->equal_3_object()(p1, p2);
    }
  };

  /*! Obtain an Equal_2 function object */
  Equal_2 equal_2_object() const { return Equal_2(this); }
  //@}

  /// \name Functor definitions for supporting intersections.
  //@{

  class Make_x_monotone_2 {
  protected:
    typedef Arr_great_circular_arc_on_sphere_traits_2<Kernel> Traits;

    /*! The traits (in case it has state) */
    const Traits * m_traits;

    /*! Constructor
     * \param traits the traits (in case it has state)
     */
    Make_x_monotone_2(const Traits * traits) : m_traits(traits) {}

    friend class Arr_great_circular_arc_on_sphere_traits_2<Kernel>;
    
  public:    
    /*! Cut the given curve into x-monotone subcurves and insert them into the
     * given output iterator. As spherical_arcs are always x_monotone, only one
     * object will be contained in the iterator.
     * \param xc the curve.
     * \param oi the output iterator, whose value-type is Object. The output
     *           object is a wrapper of either an X_monotone_curve_2, or - in
     *           case the input spherical_arc is degenerate - a Point_2 object.
     * \return the past-the-end iterator.
     */
    template<typename OutputIterator>
    OutputIterator operator()(const Curve_2 & c, OutputIterator oi) const
    {
      typedef Arr_great_circular_arc_on_sphere_traits_2<Kernel> Traits;

      if (c.is_degenerate()) {
        // The spherical_arc is a degenerate point - wrap it with an object:
        *oi++ = make_object(c.right());
        return oi;
      }

      if (c.is_x_monotone()) {
        // The spherical arc is monotone - wrap it with an object:
        // *oi++ = make_object(X_monotone_curve_2(c));
        const X_monotone_curve_2 * xc = &c;
        *oi++ = make_object(*xc);
        return oi;
      }

      if (c.is_full()) {
        // The spherical arc is full
        if (c.is_vertical()) {
          // The arc is vertical => divide it into 2 half arcs;
          const Direction_3 & np = m_traits->neg_pole();
          const Direction_3 & pp = m_traits->pos_pole();
          X_monotone_curve_2 xc1(np, pp, c.plane(), true, true);
          X_monotone_curve_2 xc2(pp, np, c.plane(), true, false);
          *oi++ = make_object(xc1);
          *oi++ = make_object(xc2);
          return oi;
        }
        // The arc is not vertical => break it at the discontinuity arc:
        const X_monotone_curve_2 xc(c.plane());
        *oi++ = make_object(xc);
        return oi;
      }
      
      const Point_2 & source = c.source();
      const Point_2 & target = c.target();
      const Plane_3 & plane = c.plane();

      if (c.is_vertical()) {
        /* If one of the endpoints coincide with a pole, divide the arc at
         * the opposite pole:
         */
        const Direction_3 & np = m_traits->neg_pole();
        const Direction_3 & pp = m_traits->pos_pole();
        if (source.is_min_boundary() || target.is_min_boundary()) {
          X_monotone_curve_2 xc1(source, pp, plane, true, true);
          X_monotone_curve_2 xc2(pp, target, plane, true, false);
          *oi++ = make_object(xc1);
          *oi++ = make_object(xc2);
          return oi;
        }

        if (source.is_max_boundary() || target.is_max_boundary()) {
          X_monotone_curve_2 xc1(source, np, plane, true, false);
          X_monotone_curve_2 xc2(np, target, plane, true, true);
          *oi++ = make_object(xc1);
          *oi++ = make_object(xc2);
          return oi;
        }

        // None of the enpoints coincide with a pole.
        Direction_3 normal = plane.orthogonal_direction();
        bool xz_plane = m_traits->x_sign(normal) == ZERO;
        Project project =
          (xz_plane) ? m_traits->project_xz : m_traits->project_yz;
        Direction_2 s = project(source);
        Direction_2 t = project(target);
        bool s_x_is_positive = m_traits->is_x_positive(s);
        bool t_x_is_positive = m_traits->is_x_positive(t);
        bool plane_is_positive = (xz_plane) ?
          (m_traits->y_sign(normal) == NEGATIVE) :
          (m_traits->x_sign(normal) == POSITIVE);
        bool ccw = ((plane_is_positive && s_x_is_positive) ||
                    (!plane_is_positive && !s_x_is_positive));
        const Point_2 & pole1 = (ccw) ? pp : np;
        X_monotone_curve_2 xc1(source, pole1, plane, true, ccw);
        *oi++ = make_object(xc1);
        if (s_x_is_positive != t_x_is_positive) {
          // Construct 1 more arc:
          X_monotone_curve_2 xc2(pole1, target, plane, true, !ccw);
          *oi++ = make_object(xc2);
          return oi;
        }
        // Construct 2 more arcs:
        const Point_2 & pole2 = (ccw) ? np : pp;
        X_monotone_curve_2 xc2(pole1, pole2, plane, true, !ccw);
        *oi++ = make_object(xc2);
        X_monotone_curve_2 xc3(pole2, target, plane, true, ccw);
        *oi++ = make_object(xc3);
        return oi;
      }

      // The curve is not vertical, (none of the enpoints coincide with a pole)
      Point_2 p(-1, 0, plane.a() / plane.c());

      Direction_2 s = project_xy(source);
      Direction_2 t = project_xy(target);
      const Direction_2 & nx = Traits::neg_x_2();
      const Kernel * kernel = m_traits;
      bool directed_right =
        kernel->counterclockwise_in_between_2_object()(nx, s, t);
      
      X_monotone_curve_2 xc1(source, p, plane, false, directed_right);
      X_monotone_curve_2 xc2(p, target, plane, false, directed_right);
      *oi++ = make_object(xc1);
      *oi++ = make_object(xc2);
      return oi;
    }
  };

  /*! Obtain a Make_x_monotone_2 function object */
  Make_x_monotone_2 make_x_monotone_2_object() const
  { return Make_x_monotone_2(this); }

  class Split_2 {
  public:
    /*! Split a given x-monotone curve at a given point into two sub-curves.
     * \param xc the curve to split
     * \param p the split point.
     * \param xc1 (output) the left resulting subcurve. p is its right
     * endpoint.
     * \param xc2 (output) the right resulting subcurve. p is its left
     * endpoint.
     * \pre p lies on xc but is not one of its endpoints.
     */
    void operator()(const X_monotone_curve_2 & xc, const Point_2 & p,
                    X_monotone_curve_2 & xc1, X_monotone_curve_2 & xc2) const
    {
      CGAL_precondition(!xc.is_degenerate());
      const Point_2 & source = xc.source();
      const Point_2 & target = xc.target();
      CGAL_precondition_code(Kernel kernel);
      CGAL_precondition_code
        (typename Kernel::Equal_3 equal_3 = kernel.equal_3_object());
      CGAL_precondition(!equal_3(p, source));
      CGAL_precondition(!equal_3(p, target));

      xc1.set_plane(xc.plane());
      xc1.set_is_vertical(xc.is_vertical());
      xc1.set_is_degenerate(false);

      xc2.set_plane(xc.plane());
      xc2.set_is_vertical(xc.is_vertical());
      xc2.set_is_degenerate(false);
      
      if (xc.is_directed_right()) {
        xc1.set_source(source);
        xc1.set_target(p);
        xc1.set_is_directed_right(true);
        xc2.set_source(p);
        xc2.set_target(target);
        xc2.set_is_directed_right(true);
      } else {
        xc1.set_source(p);
        xc1.set_target(target);
        xc1.set_is_directed_right(false);
        xc2.set_source(source);
        xc2.set_target(p);
        xc2.set_is_directed_right(false);
      }
    }
  };

  /*! Obtain a Split_2 function object */
  Split_2 split_2_object() const { return Split_2(); }

  /*! The clockwise-in-between function object */
  class Clockwise_in_between_2 {
  public:
    bool operator()(const Direction_2 & d,
                    const Direction_2 & d1, const Direction_2 & d2) const
    {
      typedef typename Kernel::Counterclockwise_in_between_2
        Counterclockwise_in_between_2;
      Kernel kernel;
      Counterclockwise_in_between_2 ccib =
        kernel.counterclockwise_in_between_2_object();
      return ccib(d, d2, d1);
    }
  };

  /*! Obtain a Clockwise_in_between function object */
  Clockwise_in_between_2 clockwise_in_between_2_object() const
  { return Clockwise_in_between_2(); }
  
  /*! The intersection computation functor */
  class Intersect_2 {
  private:
    
    /*! Computes the intersection between two arcs contained in the same plane
     * \param l1_3
     * \param r1_3
     * \param l2_3
     * \param r2_3
     * \param plane      - the common plane
     * \param vertical   - is the plane vertical
     * \param start      - the start 2d vertex
     * \param in_between - the in_between operator
     * \param project    - the projection function
     * \param oi         - the output iterator
     */
    template <typename In_between, typename OutputIterator>
    OutputIterator compute_intersection(const Point_2 & l1_3,
                                        const Point_2 r1_3,
                                        const Point_2 & l2_3,
                                        const Point_2 r2_3,
                                        const Plane_3 & plane,
                                        bool vertical,
                                        const Direction_2 & start,
                                        const In_between & in_between,
                                        Project project,
                                        OutputIterator oi) const
    {
      typedef std::pair<Point_2,unsigned int>                   Point_2_pair;
      Kernel kernel;
      typename Kernel::Equal_2 equal = kernel.equal_2_object();

      Direction_2 l1 = project(l1_3);
      Direction_2 r1 = project(r1_3);
      Direction_2 l2 = project(l2_3);
      Direction_2 r2 = project(r2_3);

      if (equal(l1, l2)) {
        const Point_2 & trg = (in_between(r1, l2, r2)) ? r1_3 : r2_3;
        X_monotone_curve_2 xc(l1_3, trg, plane, vertical, true);
        *oi++ = make_object(xc);
        return oi;
      }

      bool l1_eq_start = equal(l1, start);
      bool l2_eq_start = equal(l2, start);

      if (l1_eq_start || (!l2_eq_start && in_between(l1, start, l2))) {
        if (l1_eq_start && equal(r2, start))
          *oi++ = make_object(Point_2_pair(r2_3, 1));
        if (in_between(r1, l1, l2)) return oi;      // no intersection
        if (equal(r1, l2)) {
          *oi++ = make_object(Point_2_pair(r1_3, 1));
          return oi;
        }
        const Point_2 & trg = (in_between(r1, l2, r2)) ? r1_3 : r2_3;
        X_monotone_curve_2 xc(l2_3, trg, plane, vertical, true);
        *oi++ = make_object(xc);
        return oi;
      }
      CGAL_assertion(l2_eq_start || in_between(l2, start, l1));
      if (l2_eq_start && equal(r1, start))
        *oi++ = make_object(Point_2_pair(r1_3, 1));
      if (in_between(r2, l2, l1)) return oi;      // no intersection
      if (equal(r2, l1)) {
        *oi++ = make_object(Point_2_pair(r2_3, 1));
        return oi;
      }
      const Point_2 & trg = (in_between(r1, l2, r2)) ? r1_3 : r2_3;
      X_monotone_curve_2 xc(l1_3, trg, plane, vertical, true);
      *oi++ = make_object(xc);
      return oi;
    }
    
    /*! Determine whether a direction pierces an arc.
     * \param dir the direction.
     * \param arc the arc.
     * \return true iff dir pierces arc.
     * \pre dir lies in the plane defined by arc.
     */
    bool is_in_between
    (const Arr_extended_direction_3<Kernel> & dir,
     const Arr_x_monotone_great_circular_arc_on_sphere_3<Kernel> & arc) const
    {
      typedef Arr_great_circular_arc_on_sphere_traits_2<Kernel> Traits;

      const Point_2 & l = arc.left();
      const Point_2 & r = arc.right();

      // Handle the poles:
      if (dir.is_max_boundary()) return (r.is_max_boundary());
      if (dir.is_min_boundary()) return (l.is_min_boundary());

      // dir does not coincide with a pole:
      Direction_2 dir_xy = project_xy(dir);

      Kernel kernel;
      typename Kernel::Equal_2 equal_2 = kernel.equal_2_object(); 

      if (arc.is_vertical()) {
        // Compare the y-coords.
        const Point_2 & p = (l.is_min_boundary()) ? r : l;
        Direction_2 p_xy = project_xy(p);
        if (!equal_2(dir_xy, p_xy)) return false;

        return
          (((l.is_min_boundary()) || (Traits::compare_y(dir, l) != SMALLER)) &&
           ((r.is_max_boundary()) || (Traits::compare_y(dir, r) != LARGER)));
      }
      // arc is not vertical, compare the projections onto the xy-plane:
      Direction_2 r_xy = project_xy(r);
      if (equal_2(dir_xy, r_xy)) return true;
      Direction_2 l_xy = project_xy(l);
      if (equal_2(dir_xy, l_xy)) return true;
      return kernel.counterclockwise_in_between_2_object()(dir_xy, l_xy, r_xy);
    }

  public:
    /*! Find the intersections of the two given curves and insert them into the
     * given output iterator. As two spherical_arcs may itersect only once,
     * only a single intersection will be contained in the iterator.
     * \param xc1 the first curve.
     * \param xc2 the second curve.
     * \param oi the output iterator.
     * \return the past-the-end iterator.
     */
    template<typename OutputIterator>
    OutputIterator operator()(const X_monotone_curve_2 & xc1,
                              const X_monotone_curve_2 & xc2,
                              OutputIterator oi) const
    {
      typedef Arr_great_circular_arc_on_sphere_traits_2<Kernel> Traits;
      typedef typename Kernel::Equal_2                          Equal_2;
      typedef typename Kernel::Counterclockwise_in_between_2
        Counterclockwise_in_between_2;
      typedef typename Traits::Clockwise_in_between_2
        Clockwise_in_between_2;
        
      CGAL_precondition(!xc1.is_degenerate());
      CGAL_precondition(!xc2.is_degenerate());

      typedef std::pair<Point_2,unsigned int>         Point_2_pair;
      Kernel kernel;

#if defined(CGAL_ARR_PLANE)
      CGAL::Object obj = intersect(xc1.plane(), xc2.plane());
#else
      CGAL::Object obj = kernel.intersect_3_object()(xc1.plane(), xc2.plane());
#endif
      const Plane_3 * plane_ptr = object_cast<Plane_3>(&obj);
      if (plane_ptr != NULL) {
        Kernel kernel;
        Equal_2 equal = kernel.equal_2_object();
        Counterclockwise_in_between_2 ccib =
          kernel.counterclockwise_in_between_2_object();
        Clockwise_in_between_2 cib;

        if (xc1.is_vertical()) {
          const Plane_3 & plane1 = xc1.plane();
          const Plane_3 & plane2 = xc2.plane();
#if defined(CGAL_ARR_PLANE)
          bool res = plane1.equal(plane2);
#else
          bool res = kernel.equal_3_object()(plane1, plane2);
#endif
          if ((!res && (xc1.is_directed_right() == xc2.is_directed_right())) ||
              (res && (xc1.is_directed_right() != xc2.is_directed_right())))
          {
            if (xc1.left().is_min_boundary() && xc2.left().is_min_boundary())
              *oi++ = make_object(Point_2_pair(xc1.left(), 1));
            if (xc1.right().is_max_boundary() && xc2.right().is_max_boundary())
              *oi++ = make_object(Point_2_pair(xc1.right(), 1));
            return oi;
          }
            
          /*! If the endpoints of one arc coinside with the 2 poles resp,
           * the other arc is completely overlapping.
           */
          if (xc1.left().is_min_boundary() && xc1.right().is_max_boundary()) {
            *oi++ = make_object(xc2);
            return oi;
          }
          if (xc2.left().is_min_boundary() && xc2.right().is_max_boundary()) {
            *oi++ = make_object(xc1);
            return oi;
          }
          /*! Find an endpoint that does not coincide with a pole, and project
           * it onto the xy plane. If the projection coincide with the negative
           * x, project onto the zx plane. Otherwise project onto the yz plane.
           */
          const Point_2 & p_3 =
            xc1.left().is_min_boundary() ? xc1.right() : xc1.left();
          const Direction_2 & nx = Traits::neg_x_2();
          Direction_2 p = Traits::project_xy(p_3);
          if (Traits::orientation(nx, p) == COLLINEAR) {
            // Project onto zx plane:

            /*! All projected enpoints reside in one (closed) x half-space -
             * either in the negative x half space or the positive one.
             */
            if (p.dx() > 0) {
              // The endpoints reside in the positive x-halfspace:
              return compute_intersection(xc1.left(), xc1.right(),
                                          xc2.left(), xc2.right(),
                                          xc1.plane(), true, Traits::neg_y_2(),
                                          ccib, Traits::project_xz, oi);
            }
            // The endpoints reside in the negative x-halfspace:
            return compute_intersection(xc1.left(), xc1.right(),
                                        xc2.left(), xc2.right(),
                                        xc1.plane(), true, Traits::neg_y_2(),
                                        cib, Traits::project_xz, oi);
          }
          // Project onto yz plane:    

          /*! All projected enpoints reside in one (closed) x half-space -
           * either in the negative x half space or the positive one.
           */
          if (p.dy() > 0) {
            // The endpoints reside in the positive x-halfspace:
            return compute_intersection(xc1.left(), xc1.right(),
                                        xc2.left(), xc2.right(),
                                        xc1.plane(), true, Traits::neg_y_2(),
                                        ccib, Traits::project_yz, oi);
          }
          // The endpoints reside in the negative x-halfspace:
          return compute_intersection(xc1.left(), xc1.right(),
                                      xc2.left(), xc2.right(),
                                      xc1.plane(), true, Traits::neg_y_2(),
                                      cib, Traits::project_yz, oi);
        }

        // The arcs are not vertical:
        return compute_intersection(xc1.left(), xc1.right(),
                                    xc2.left(), xc2.right(),
                                    xc1.plane(), false, Traits::neg_x_2(),
                                    ccib, Traits::project_xy, oi);
      }
      
      const Line_3 * line_ptr = object_cast<Line_3>(&obj);
      if (line_ptr != NULL) {
        Point_3 p = line_ptr->point(1);
        Vector_3 v = kernel.construct_vector_3_object()(ORIGIN, p);
        Direction_3 d = kernel.construct_direction_3_object()(v);
        Point_2 ed(d);

        // Determine which one of the two directions:
        if (is_in_between(ed, xc1) && is_in_between(ed, xc2)) {
          *oi++ = make_object(Point_2_pair(ed, 1));
          return oi;
        }
        Point_2 edo(kernel.construct_opposite_direction_3_object()(d));
        if (is_in_between(edo, xc1) && is_in_between(edo, xc2)) {
          *oi++ = make_object(Point_2_pair(edo, 1));
          return oi;
        }
        return oi;
      }
      // Should not reach here!
      CGAL_assertion(0);
      return oi;
    }
  };

  /*! Obtain an Intersect_2 function object */
  Intersect_2 intersect_2_object() const { return Intersect_2(); }

  class Are_mergeable_2 {
  public:
    /*! Check whether it is possible to merge two given x-monotone curves.
     * \param xc1 the first curve.
     * \param xc2 the second curve.
     * \return true if the two arcs are mergeable; false otherwise.
     * Two arcs are mergeable if:
     * 1. they are supported by the same plane, and
     * 2. share a common endpoint that is not on the discontinuity arc
     */
    bool operator()(const X_monotone_curve_2 & xc1,
                    const X_monotone_curve_2 & xc2) const
    {
      CGAL_precondition(!xc1.is_degenerate());
      CGAL_precondition(!xc2.is_degenerate());

      Kernel kernel;
      typename Kernel::Equal_3 equal = kernel.equal_3_object();
#if defined(CGAL_ARR_PLANE)
      if (!(xc1.plane()).equal(xc2.plane())) return false;
#else
      if (!equal(xc1.plane(), xc2.plane())) return false;
#endif
      if (equal(xc1.right(), xc2.left()) && xc2.left().is_no_boundary())
        return true;
      if (equal(xc1.left(), xc2.right()) && xc1.left().is_no_boundary())
        return true;
      return false;
    }
  };

  /*! Obtain an Are_mergeable_2 function object */
  Are_mergeable_2 are_mergeable_2_object() const { return Are_mergeable_2(); }

  class Merge_2 {
  protected:
    typedef Arr_great_circular_arc_on_sphere_traits_2<Kernel> Traits;

    /*! The traits (in case it has state) */
    const Traits * m_traits;

    /*! Constructor
     * \param traits the traits (in case it has state)
     */
    Merge_2(const Traits * traits) : m_traits(traits) {}

    friend class Arr_great_circular_arc_on_sphere_traits_2<Kernel>;
    
  public:
    /*! Merge two given x-monotone curves into a single curve (spherical_arc).
     * \param xc1 the first curve.
     * \param xc2 the second curve.
     * \param xc Output: the merged curve.
     * \pre the two curves are mergeable. That is, they are supported by the
     *      same plane or oposite planes and share a common endpoint that is
     *      not on the discontinuity arc.
     */
    void operator()(const X_monotone_curve_2 & xc1,
                    const X_monotone_curve_2 & xc2,
                    X_monotone_curve_2 & xc) const
    {
      CGAL_precondition(!xc1.is_degenerate());
      CGAL_precondition(!xc2.is_degenerate());

      const Kernel * kernel = m_traits;
      typename Kernel::Equal_3 equal = kernel->equal_3_object();

      CGAL_precondition_code(Are_mergeable_2 are_merg;);
      CGAL_precondition (are_merg(xc1, xc2) == true);

      xc.set_is_degenerate(false);
      xc.set_is_vertical(xc1.is_vertical());

      if (xc1.is_directed_right() || xc2.is_directed_right()) {
        xc.set_plane(xc1.is_directed_right() ? xc1.plane() : xc2.plane());
        xc.set_is_directed_right(true);

        if (equal(xc1.right(), xc2.left())) {
          xc.set_source(xc1.left());
          xc.set_target(xc2.right());
        } else {
          CGAL_assertion(equal(xc1.left(), xc2.right()));
          xc.set_source(xc2.left());
          xc.set_target(xc1.right());
        }
      } else {
        xc.set_plane(xc1.plane());
        xc.set_is_directed_right(false);

        if (equal(xc1.right(), xc2.left())) {
          xc.set_source(xc2.right());
          xc.set_target(xc1.left());
        } else {
          CGAL_assertion(equal(xc1.left(), xc2.right()));
          xc.set_source(xc1.right());
          xc.set_target(xc2.left());
        }
      }

      /* The arc is full if:
       * 1. the source lies on the open discontinuity arc, and
       * 2. the target lies on the open discontinuity arc, and
       * 3. the arc is not vertical
       */
      xc.set_is_full(!xc.is_vertical() &&
                     xc.source().is_mid_boundary() &&
                     xc.target().is_mid_boundary());
    }      
  };

  /*! Obtain a Merge_2 function object */
  Merge_2 merge_2_object() const { return Merge_2(this); }
  //@}

  /// \name Functor definitions for the landmarks point-location strategy.
  //@{
  typedef double                          Approximate_number_type;

  class Approximate_2 {
  public:

    /*! Return an approximation of a point coordinate.
     * \param p the exact point.
     * \param i the coordinate index (either 0 or 1).
     * \pre i is either 0 or 1.
     * \return an approximation of p's x-coordinate (if i == 0), or an 
     *         approximation of p's y-coordinate (if i == 1).
     */
    Approximate_number_type operator()(const Point_2 & p, int i) const
    {
      CGAL_precondition(i == 0 || i == 1);
      return (i == 0) ? CGAL::to_double(p.x()) : CGAL::to_double(p.y());
    }
  };

  /*! Obtain an Approximate_2 function object */
  Approximate_2 approximate_2_object() const { return Approximate_2(); }

  class Construct_x_monotone_curve_2 {
  public:

    /*! Return an x-monotone curve connecting the two given endpoints.
     * \param p the first point.
     * \param q the second point.
     * \pre p and q must not be the same.
     * \return a spherical_arc connecting p and q.
     */
    X_monotone_curve_2 operator()(const Point_2 & p, const Point_2 & q) const
    { return X_monotone_curve_2(p, q); }
  };

  /*! Obtain a Construct_x_monotone_curve_2 function object */
  Construct_x_monotone_curve_2 construct_x_monotone_curve_2_object() const
  { return Construct_x_monotone_curve_2(); }
  //@}


  /// \name Functor definitions for the Boolean set-operation traits.
  //@{
 
  class Compare_endpoints_xy_2 {
  public:

    /*!
     * Compare the endpoints of an $x$-monotone curve lexicographically.
     * (assuming the curve has a designated source and target points).
     * \param xc the curve.
     * \return SMALLER if the curve is directed right;
     *         LARGER if the curve is directed left.
     */
    Comparison_result operator()(const X_monotone_curve_2 & xc)
    { return (xc.is_directed_right()) ? SMALLER : LARGER; }
  };

  /*! Obtain a Compare_endpoints_xy_2 function object */
  Compare_endpoints_xy_2 compare_endpoints_xy_2_object() const
  { return Compare_endpoints_xy_2(); }

  class Construct_opposite_2 {
  public:
    /*! Construct an opposite x-monotone (with swapped source and target).
     * \param xc the curve.
     * \return the opposite curve.
     */
    X_monotone_curve_2 operator()(const X_monotone_curve_2 & xc)
    { return xc.opposite(); }
  };

  /*! Obtain a Construct_opposite_2 function object */
  Construct_opposite_2 construct_opposite_2_object() const
  { return Construct_opposite_2(); }
  //@}

#if 0
  /*! Inserter for the spherical_arc class used by the traits-class */
  template <typename OutputStream>
  friend OutputStream & operator<<(OutputStream & os, const Point_2 & p)
  {
    CGAL::To_double<typename Kernel::FT> todouble;
    os << static_cast<float>(todouble(p.dx())) << ", "
       << static_cast<float>(todouble(p.dy())) << ", "
       << static_cast<float>(todouble(p.dz()));
    return os;
  }

  /*! Inserter for the spherical_arc class used by the traits-class */
  template <typename OutputStream>
  friend OutputStream & operator<<(OutputStream & os,
                                   const X_monotone_curve_2 & xc)
  {
    os << "(" << xc.left() << "), (" << xc.right() << ")";
    return os;
  }

  /*! Extractor for the spherical_arc class used by the traits-class */
  template <typename InputStream>
  friend InputStream & operator>>(InputStream & is, X_monotone_curve_2 & arc)
  {
    std::cerr << "Not implemented yet!" << std::endl;
    return is;
  }  
#endif
};

/*! Represent an extended 3D direction that is used in turn to represent a
 * spherical-arc endpoint. The extended data consists of two flags that
 * indicate whether the point is on the x and on a y boundaries,
 * respectively.
 */
template <typename Kernel>
class Arr_extended_direction_3 : public Kernel::Direction_3 {
public:
  typedef typename Kernel::FT                           FT;
  typedef typename Kernel::Direction_3                  Direction_3;

  /*! Enumeration of discontinuity type */
  enum Location_type {
    NO_BOUNDARY_LOC,
    MIN_BOUNDARY_LOC,
    MID_BOUNDARY_LOC,
    MAX_BOUNDARY_LOC
  };

private:
  typedef typename Kernel::Direction_2                  Direction_2;

  /*! The point discontinuity type */
  Location_type m_location;

public:
  /*! Default constructor */
  Arr_extended_direction_3() : 
    Direction_3(0, 0, 1),
    m_location(MAX_BOUNDARY_LOC)
  {}
      
  /*! Constructor */
  Arr_extended_direction_3(const Direction_3 & dir,
                           Location_type location) :
    Direction_3(dir),
    m_location(location)
  {}

  /*! Constructor
   * \param x
   * \param y
   * \param z
   */
  Arr_extended_direction_3(const FT & x, const FT & y, const FT & z) :
    Direction_3(x, y, z)
  {
    m_location =
      (CGAL::sign(y) != ZERO) ? NO_BOUNDARY_LOC :
      ((CGAL::sign(x) == POSITIVE) ? NO_BOUNDARY_LOC :
       ((CGAL::sign(x) == NEGATIVE) ? MID_BOUNDARY_LOC :
        ((CGAL::sign(z) == NEGATIVE) ? MIN_BOUNDARY_LOC : MAX_BOUNDARY_LOC)));
  }
  
  /*! Constructor from a direction
   * \param dir the direction
   */
  Arr_extended_direction_3(const Direction_3 & dir) : Direction_3(dir)
  {
    typedef Arr_great_circular_arc_on_sphere_traits_2<Kernel> Traits;
    
    const Direction_3 & pp = Traits::pos_pole();
    const Direction_3 & np = Traits::neg_pole();
    Kernel kernel;
    typename Kernel::Equal_3 equal_3 = kernel.equal_3_object();
    if (equal_3(dir, pp)) m_location = MAX_BOUNDARY_LOC;
    else if (equal_3(dir, np)) m_location = MIN_BOUNDARY_LOC;
    else {
      Direction_2 dir_xy = Traits::project_xy(dir);
      typename Kernel::Equal_2 equal_2 = kernel.equal_2_object();
      const Direction_2 & nx = Traits::neg_x_2();
      m_location = equal_2(dir_xy, nx) ? MID_BOUNDARY_LOC : NO_BOUNDARY_LOC;
    }
  }

  /*! Copy constructor */
  Arr_extended_direction_3(const Arr_extended_direction_3 & ed) :
    Direction_3(static_cast<const Direction_3&>(ed))
  {
    m_location = ed.discontinuity_type();
  }

  /*! Assignment operator. */
  Arr_extended_direction_3 & operator=(const Arr_extended_direction_3 & ed)
  {
    *(static_cast<Direction_3*>(this)) = static_cast<const Direction_3&>(ed);
    m_location = ed.discontinuity_type();
    return (*this);
  }
    
  /*! Obtain the discontinuity type of the point */
  Location_type discontinuity_type() const
  { return m_location; }
  
  bool is_no_boundary() const { return (m_location == NO_BOUNDARY_LOC); }
  
  bool is_min_boundary() const { return (m_location == MIN_BOUNDARY_LOC); }
  
  bool is_mid_boundary() const { return (m_location == MID_BOUNDARY_LOC); }
  
  bool is_max_boundary() const { return (m_location == MAX_BOUNDARY_LOC); }
};

/*! A Representation of an x-monotone great circular arc embedded on a sphere,
 * as used by the Arr_great_circular_arc_on_sphere_traits_2 traits-class
 * An x-monotone great circular arc cannot cross the closed hemi-circle arc of
 * discontinuity, defined as the longitude that lies in the zx-plane, and is
 * contained in the open halfspace (x > 0).
 * \todo At this point such an arc cannot have an angle of 180 degrees.
 * \todo It is always directed from its source to its target.
 */
template <typename T_Kernel>
class Arr_x_monotone_great_circular_arc_on_sphere_3 {
protected:
  typedef T_Kernel                                              Kernel;
  
#if defined(CGAL_ARR_PLANE)
  typedef Arr_plane_3<Kernel>                                   Plane_3;
#else
  typedef typename Kernel::Plane_3                              Plane_3;
#endif
  typedef typename Kernel::Point_3                              Point_3;
  typedef typename Kernel::Ray_3                                Ray_3;
  typedef typename Kernel::Vector_3                             Vector_3;

  typedef typename Kernel::Direction_2                          Direction_2;

  // For some reason compilation under Windows fails without the qualifier
  typedef CGAL::Arr_extended_direction_3<Kernel>    Arr_extended_direction_3;

  typedef typename Arr_extended_direction_3::Direction_3        Direction_3;

  Arr_extended_direction_3 m_source;    // The source point of the arc
  Arr_extended_direction_3 m_target;    // The target point of the arc
  Plane_3 m_plane;                      // The plane that contains the arc
  bool m_is_vertical;                   // The arc is vertical
  bool m_is_directed_right;   // Target (lexicographically) larger than source
  bool m_is_full;                       // The arc is a full circle
  bool m_is_degenerate;                 // The arc is degenerate (single point)

  /*! Is a given direction colinear with the x-axis?
   * \param d the direction
   * \return true iff d is directed towards the positive or negative x axis
   */
  inline bool is_colinear_x(Direction_2 d)
  { return (CGAL::sign(d.dy()) == ZERO); }

  /*! Is the x-coordinate of a given direction positive
   * \param d the direction
   * \return true if the x-coordinate of d is possitive and false otherwise
   */
  inline bool is_x_positive(Direction_2 d)
  { return (CGAL::sign(d.dx()) == POSITIVE); }

  /*! Is the x-coordinate of a given direction negive
   * \param d the direction
   * \return true if the x-coordinate of d is negative and false otherwise
   */
  inline bool is_x_negative(Direction_2 d)
  { return (CGAL::sign(d.dx()) == NEGATIVE); }
  
  inline Sign x_sign(Direction_3 d) { return CGAL::sign(d.dx()); }

  inline Sign y_sign(Direction_3 d) { return CGAL::sign(d.dy()); }  

  inline Sign z_sign(Direction_3 d) { return CGAL::sign(d.dz()); }

  /*! Determined whether a direction is contained in a plane
   * \param plane the 3D plane.
   * \param dir the 3D direction.
   * \return true if dir is contained in plane; false otherwise.
   * \pre the plane contains the origin.
   */
  inline bool has_on(const Plane_3 & plane, const Direction_3 & dir) const
  {
    Kernel kernel;
    Ray_3 ray = kernel.construct_ray_3_object()(ORIGIN, dir);
    Vector_3 vec = kernel.construct_vector_3_object()(ray);
    Point_3 point = kernel.construct_translated_point_3_object()(ORIGIN, vec);
    return kernel.has_on_3_object()(plane, point);
  }
  
  /*! Constructs a plane that contains two directions.
   * \todo Introduce in Kernel::ConstructPlane_3::operator()(Direction_3, Dir..)
   * \param d1 the first direction.
   * \param d2 the second direction.
   */
  inline Plane_3 construct_plane_3(const Direction_3 & d1,
                                   const Direction_3 & d2) const
  {
    Kernel kernel;

    Ray_3 r1 = kernel.construct_ray_3_object()(ORIGIN, d1);
    Vector_3 v1 = kernel.construct_vector_3_object()(r1);
    Point_3 p1 = kernel.construct_translated_point_3_object()(ORIGIN, v1);

    Ray_3 r2 = kernel.construct_ray_3_object()(ORIGIN, d2);
    Vector_3 v2 = kernel.construct_vector_3_object()(r2);
    Point_3 p2 = kernel.construct_translated_point_3_object()(ORIGIN, v2);

#if defined(CGAL_ARR_PLANE)
    Plane_3 plane(p1, p2);
#else
    Plane_3 plane = kernel.construct_plane_3_object()(ORIGIN, p1, p2);
#endif
    return plane;
  }

public:
  /*! Default constructor */
  Arr_x_monotone_great_circular_arc_on_sphere_3() :
    m_is_vertical(false),
    m_is_directed_right(false),
    m_is_full(false),
    m_is_degenerate(true)
  {}

  /*! Constructor
   * \param src the source point of the arc
   * \param trg the target point of the arc
   * \param plane the plane that contains the arc
   * \param is_vertical is the arc vertical ?
   * \param is_directed_right is the arc directed from left to right?
   * \param is_full is the arc a full circle?
   * \param is_degenerate is the arc degenerate (single point)?
   */
  Arr_x_monotone_great_circular_arc_on_sphere_3
  (const Arr_extended_direction_3 & src,
   const Arr_extended_direction_3 & trg,
   const Plane_3 & plane,
   bool is_vertical, bool is_directed_right,
   bool is_full = false, bool is_degenerate = false) :
    m_source(src),
    m_target(trg),
    m_plane(plane),
    m_is_vertical(is_vertical),
    m_is_directed_right(is_directed_right),
    m_is_full(is_full),
    m_is_degenerate(is_degenerate)
  {}

  /*! Copy constructor
   * \param other the other arc
   */
  Arr_x_monotone_great_circular_arc_on_sphere_3
  (const Arr_x_monotone_great_circular_arc_on_sphere_3 & other)
  {
    m_source = other.m_source;
    m_target = other.m_target;
    m_plane = other.m_plane;
    m_is_vertical = other.m_is_vertical;
    m_is_directed_right = other.m_is_directed_right;
    m_is_full = other.m_is_full;
    m_is_degenerate = other.m_is_degenerate;
  }
  
  /*! Construct a spherical_arc from two endpoint directions. It is assumed
   * that the arc is the one with the smaller angle among the two.
   * 1. Find out whether the arc is x-monotone.
   * 2. If it is x-monotone,
   *    2.1 Find out whether it is vertical, and
   *    2.2 whether the target is larger than the source (directed right).
   * The arc is vertical, iff
   * 1. one of its endpoint direction pierces a pole, or
   * 2. the projections onto the xy-plane coincide.
   * \param source the source point.
   * \param target the target point.
   * \pre the source and target cannot be equal.
   * \pre the source and target cannot be opposite of each other.
   */
  Arr_x_monotone_great_circular_arc_on_sphere_3
  (const Arr_extended_direction_3 & source,
   const Arr_extended_direction_3 & target) :
    m_source(source),
    m_target(target),
    m_is_full(false),
    m_is_degenerate(false)
  {
    typedef Arr_great_circular_arc_on_sphere_traits_2<Kernel> Traits;

    Kernel kernel;
    CGAL_precondition(!kernel.equal_3_object()(source, target));
    CGAL_precondition(!kernel.equal_3_object()
                      (kernel.construct_opposite_direction_3_object()(source),
                       target));
    m_plane = construct_plane_3(source, target);
      
    // Check whether any one of the endpoint coincide with a pole:
    if (source.is_max_boundary()) {
      set_is_vertical(true);
      set_is_directed_right(false);
      return;
    }
    if (source.is_min_boundary()) {
      set_is_vertical(true);
      set_is_directed_right(true);
      return;
    }
    if (target.is_max_boundary()) {
      set_is_vertical(true);
      set_is_directed_right(true);
      return;
    }
    if (target.is_min_boundary()) {
      set_is_vertical(true);
      set_is_directed_right(false);
      return;
    }

    // None of the enpoints coincide with a pole:
    typename Kernel::Equal_2 equal_2 = kernel.equal_2_object();
    Direction_2 s = Traits::project_xy(source);
    Direction_2 t = Traits::project_xy(target);

    Orientation orient = Traits::orientation(s, t);
    if (orient == COLLINEAR) {
      set_is_vertical(true);
      const Direction_2 & nx = Traits::neg_x_2();
      if (Traits::orientation(nx, s) == COLLINEAR) {
        // Project onto xz plane:
        s = Traits::project_xz(source);
        t = Traits::project_xz(target);
        const Direction_2 & ny = Traits::neg_y_2();
        Orientation orient1 = Traits::orientation(ny, s);
        CGAL_assertion_code(Orientation orient2 = Traits::orientation(ny, t));
        CGAL_assertion(orient1 == orient2);
        orient = Traits::orientation(s, t);
        CGAL_assertion(orient != COLLINEAR);
        if (orient1 == LEFT_TURN) {
          set_is_directed_right(orient == LEFT_TURN);
          return;
        }
        set_is_directed_right(orient == RIGHT_TURN);
        return;
      }
      // Project onto yz plane:
      s = Traits::project_yz(source);
      t = Traits::project_yz(target);
      const Direction_2 & ny = Traits::neg_y_2();
      Orientation orient1 = Traits::orientation(ny, s);
      CGAL_assertion_code(Orientation orient2 = Traits::orientation(ny, t));
      CGAL_assertion(orient1 == orient2);
      if (orient1 == LEFT_TURN) {
        orient = Traits::orientation(s, t);
        CGAL_assertion(orient != COLLINEAR);
        set_is_directed_right(orient == LEFT_TURN);
        return;
      }
      orient = Traits::orientation(s, t);
      CGAL_assertion(orient != COLLINEAR);
      set_is_directed_right(orient == RIGHT_TURN);
      return;
    }
    
    // The arc is not vertical!
    set_is_vertical(false);
    set_is_directed_right(orient == LEFT_TURN);
    set_is_full(kernel.equal_3_object()(source, target));
  }

  /*! Construct a full spherical_arc from a plane
   * \param plane the containing plane.
   * \pre the plane is not vertical
   */
  Arr_x_monotone_great_circular_arc_on_sphere_3(const Plane_3 & plane) :
    m_plane(plane),
    m_is_vertical(false),
    m_is_directed_right(z_sign(plane.orthogonal_direction()) == POSITIVE),
    m_is_full(true),
    m_is_degenerate(false)
  {
    CGAL_precondition(z_sign(plane.orthogonal_direction()) != ZERO);

    Direction_3 d(-1, 0, plane.a() / plane.c());
    m_source = m_target =
      Arr_extended_direction_3(d, Arr_extended_direction_3::MID_BOUNDARY_LOC);
  }

  /*! Construct a full spherical_arc from a common endpoint and a plane
   * \param plane the containing plane.
   * \pre the point lies on the plane
   * \pre the point lies on the open discontinuity arc
   */
  Arr_x_monotone_great_circular_arc_on_sphere_3
  (const Arr_extended_direction_3 & point, const Plane_3 & plane) :
    m_source(point),
    m_target(point),
    m_plane(plane),
    m_is_vertical(false),
    m_is_directed_right(z_sign(plane.orthogonal_direction()) == POSITIVE),
    m_is_full(true),
    m_is_degenerate(false)
  {
    CGAL_precondition(has_on(plane, point));
    CGAL_precondition(z_sign(plane.orthogonal_direction()) != ZERO);
  }
  
  /*! Construct a spherical_arc from two endpoints directions contained
   * in a plane.
   * \param plane the containing plane.
   * \param source the source-point direction.
   * \param target the target-point direction.
   * \pre Both endpoint lie on the given plane.
   * \pre Both endpoint lie on the given plane.
   */
  Arr_x_monotone_great_circular_arc_on_sphere_3
  (const Arr_extended_direction_3 & source,
   const Arr_extended_direction_3 & target,
   const Plane_3 & plane) :
    m_source(source),
    m_target(target),
    m_plane(plane),
    m_is_full(false),
    m_is_degenerate(false)
  {
    typedef Arr_great_circular_arc_on_sphere_traits_2<Kernel> Traits;

    CGAL_precondition(has_on(plane, source));
    CGAL_precondition(has_on(plane, target));

    // Check whether any one of the endpoint coincide with a pole:
    if (source.is_max_boundary()) {
      set_is_vertical(true);
      set_is_directed_right(false);
      return;
    }
    if (source.is_min_boundary()) {
      set_is_vertical(true);
      set_is_directed_right(true);
      return;
    }
    if (target.is_max_boundary()) {
      set_is_vertical(true);
      set_is_directed_right(true);
      return;
    }
    if (target.is_min_boundary()) {
      set_is_vertical(true);
      set_is_directed_right(false);
      return;
    }

    Direction_3 normal = plane.orthogonal_direction();
    if (z_sign(normal) == ZERO) {
      set_is_vertical(true);

      bool xz_plane = x_sign(normal) == ZERO;
      typename Traits::Project project =
        (xz_plane) ? Traits::project_xz : Traits::project_yz;
      Direction_2 s = project(source);
      Direction_2 t = project(target);
      bool s_x_is_positive = is_x_positive(s);
      bool t_x_is_positive = is_x_positive(t);
      bool plane_is_positive = (xz_plane) ?
        (y_sign(normal) == NEGATIVE) : (x_sign(normal) == POSITIVE);
      bool ccw = ((plane_is_positive && s_x_is_positive) ||
                  (!plane_is_positive && !s_x_is_positive));
      set_is_directed_right(ccw);
      return;
    }
      
    // The arc is not vertical!
    set_is_vertical(false);
    set_is_directed_right(z_sign(normal) == POSITIVE);
  }

  /*! Set the source endpoint direction.
   * \param p the endpoint to set.
   */
  void set_source(const Direction_3 & p) { m_source = p; }

  /*! Set the target endpoint direction.
   * \param p the endpoint to set.
   */
  void set_target(const Direction_3 & p) { m_target = p; }

  /*! Set the underlying plane.
   * \param plane the plane.
   */
  void set_plane(const Plane_3 & plane) { m_plane = plane; }

  void set_is_vertical(bool flag) { m_is_vertical = flag; }
  void set_is_directed_right(bool flag) { m_is_directed_right = flag; }
  void set_is_full(bool flag) { m_is_full = flag; }
  void set_is_degenerate(bool flag) { m_is_degenerate = flag; }

  /*! Obtain the source */
  const Arr_extended_direction_3 & source() const { return m_source; }

  /*! Obtain the target */
  const Arr_extended_direction_3 & target() const { return m_target; }
    
  /*! Obtain the containing plane */
  const Plane_3 & plane() const { return m_plane; }

  /*! Obtain the (lexicographically) left endpoint direction */
  const Arr_extended_direction_3 & left() const
  { return (m_is_directed_right ? m_source : m_target); }

  /*! Obtain the (lexicographically) right endpoint */
  const Arr_extended_direction_3 & right() const
  { return (m_is_directed_right ? m_target : m_source); }

  /*! Determines whether the curve is vertical */
  bool is_vertical() const { return m_is_vertical; }

  /*! Determines whether the curve is directed lexicographically from left to
   * right
   */
  bool is_directed_right() const { return m_is_directed_right; }

  /*! Determines whether the curve is a full circle */
  bool is_full() const { return m_is_full; }

  /*! Determines whether the curve is degenerate */
  bool is_degenerate() const { return m_is_degenerate; }

  /*! Determine whether both endpoints are on the boundary */
  bool is_on_boundary() const
  { return ((!m_source.is_no_boundary()) && (!m_target.is_no_boundary())); }
    
  /*! Determine whether the given point is in the x-range of the
   * spherical_arc.
   * \param p the query point direction.
   * \return true if p is in the x-range of the (closed) spherical_arc and
   * false otherwise.
   * \pre p does not coincide with one of the poles
   */
  bool is_in_x_range(const Arr_extended_direction_3 & p) const
  {
    typedef Arr_great_circular_arc_on_sphere_traits_2<Kernel> Traits;

    CGAL_precondition(!p.is_min_boundary() && !p.is_max_boundary());
    
    if (is_vertical()) {
      if (left().is_min_boundary() && right().is_max_boundary()) {
        // Both endpoints coincide with the poles resp.
        CGAL_assertion_msg(0, "Not implemented yet!");
      }
      // At least one endpoint does not coincide with a pole.
      // Obtain the endpoint that does not coincide with a pole:
      const Arr_extended_direction_3 & q =
        (left().is_min_boundary()) ? right() : left();

      Direction_2 p_2 = Traits::project_xy(p);
      Direction_2 q_2 = Traits::project_xy(q);
      Kernel kernel;
      return kernel.equal_2_object()(p_2, q_2);
    }

    // The curve is not vertical:
    Direction_2 p_2 = Traits::project_xy(p);
    Direction_2 r = Traits::project_xy(right());
    Kernel kernel;
    if (kernel.equal_2_object()(p_2, r)) return true;
    Direction_2 l = Traits::project_xy(left());
    if (kernel.equal_2_object()(p_2, l)) return true;
    return kernel.counterclockwise_in_between_2_object()(p_2, l, r);
  }

#if 0
  /*! Create a bounding box for the spherical_arc */
  Bbox_2 bbox() const
  {
    Kernel kernel;
    Segment_2 seg = kernel.construct_spherical_arc_2_object()(this->m_source,
                                                              this->m_target);
    return kernel.construct_bbox_2_object()(seg);
  }
#endif
  
  /*! Flip the spherical_arc (swap it source and target) */
  Arr_x_monotone_great_circular_arc_on_sphere_3 opposite() const
  {
    Arr_x_monotone_great_circular_arc_on_sphere_3 opp;
    opp.m_sourse = this->m_target;
    opp.m_target = this->m_sourse;
    opp.m_plane = this->m_plane;
    opp.m_is_directed_right = !(this->is_directed_right());
    opp.m_is_vertical = this->is_vertical();
    opp.m_is_full = this->is_full();
    opp.m_is_degenerate = this->is_degenerate();
    return opp;
  }
};

/*! A representation of a general great circular arc embedded on a sphere,
 * used by the Arr_great_circular_arc_on_sphere_traits_2 traits-class
 * An arc is uniqely represented by a plane p, and two endpoints the source
 * s and the target t, which lie in the plane p. The points of the arc are
 * the locus of points visited when moving from the source s toward the
 * target t on the plane p in counterclockwise direction along the circle
 * defined by s and t.
 */
template <typename T_Kernel>
class Arr_great_circular_arc_on_sphere_3 :
  public Arr_x_monotone_great_circular_arc_on_sphere_3<T_Kernel> {
protected:
  typedef T_Kernel                                              Kernel;
  typedef Arr_x_monotone_great_circular_arc_on_sphere_3<Kernel> Base;

  typedef typename Base::Plane_3                                Plane_3;
  typedef typename Base::Direction_3                            Direction_3;
  typedef typename Base::Direction_2                            Direction_2;
  
  // For some reason compilation under Windows fails without the qualifier
  typedef CGAL::Arr_extended_direction_3<Kernel>    Arr_extended_direction_3;

  /*! Indicates whether the arc is x-monotone */
  bool m_is_x_monotone;
  
public:
  /*! Default constructor */
  Arr_great_circular_arc_on_sphere_3() : Base(), m_is_x_monotone(false) {}

  /*! Copy constructor
   * \param other the other arc
   */
  Arr_great_circular_arc_on_sphere_3
  (const Arr_great_circular_arc_on_sphere_3 & other) : Base(other)
  {
    m_is_x_monotone = other.m_is_x_monotone;
  }
  
  /*! Constructor
   * \param src the source point of the arc
   * \param trg the target point of the arc
   * \param plane the plane that contains the arc
   * \param is_x_monotone is arc  x-monotone ?
   * \param is_vertical is the arc vertical ?
   * \param is_directed_right is the arc directed from left to right?
   * \param is_full is the arc a full (great) circle?
   * \param is_degenerate is the arc degenerate (single point)?
   */
  Arr_great_circular_arc_on_sphere_3(const Arr_extended_direction_3 & src,
                                     const Arr_extended_direction_3 & trg,
                                     const Plane_3 & plane,
                                     bool is_x_monotone, bool is_vertical,
                                     bool is_directed_right,
                                     bool is_full = false,
                                     bool is_degenerate = false) :
    Base(src, trg, plane,
         is_vertical, is_directed_right, is_full, is_degenerate)
  {
    set_is_x_monotone(is_x_monotone);
  }

  /*! Construct a spherical_arc from two endpoint directions. It is assumed
   * that the arc is the one with the smaller angle among the two.
   * 1. Find out whether the arc is x-monotone.
   * 2. If it is x-monotone,
   *    2.1 Find out whether it is vertical, and
   *    2.2 whether the target is larger than the source (directed right).
   * The arc is vertical, iff
   * 1. one of its endpoint direction pierces a pole, or
   * 2. the projections onto the xy-plane coincide.
   * \param source the source point.
   * \param target the target point.
   * \pre the source and target cannot be equal.
   * \pre the source and target cannot be the opoosite of each other.
   */
  Arr_great_circular_arc_on_sphere_3(const Arr_extended_direction_3 & source,
                                     const Arr_extended_direction_3 & target)
  {
    this->set_source(source);
    this->set_target(target);
    this->set_is_full(false);
    this->set_is_degenerate(false);

    typedef Arr_great_circular_arc_on_sphere_traits_2<Kernel>   Traits;
    typedef typename Kernel::Direction_2                        Direction_2;
    typedef typename Kernel::Direction_3                        Direction_3;
    
    Kernel kernel;
    CGAL_precondition(!kernel.equal_3_object()(source, target));
    CGAL_precondition(!kernel.equal_3_object()
                      (kernel.construct_opposite_direction_3_object()(source),
                       target));
    this->m_plane = this->construct_plane_3(source, target);

    // Check whether one of the endpoints coincides with a pole: */
    if (source.is_max_boundary()) {
      this->set_is_vertical(true);
      this->set_is_directed_right(false);
      set_is_x_monotone(true);
      return;
    }
    if (source.is_min_boundary()) {
      this->set_is_vertical(true);
      this->set_is_directed_right(true);
      set_is_x_monotone(true);
      return;
    }
    if (target.is_max_boundary()) {
      this->set_is_vertical(true);
      this->set_is_directed_right(true);
      set_is_x_monotone(true);
      return;
    }
    if (target.is_min_boundary()) {
      this->set_is_vertical(true);
      this->set_is_directed_right(false);
      set_is_x_monotone(true);
      return;
    }

    // None of the enpoints coincide with a pole:
    Direction_3 normal = this->m_plane.orthogonal_direction();
    if (z_sign(normal) == ZERO) {
      // The arc is vertical
      this->set_is_vertical(true);

      bool xz_plane = (x_sign(normal) == ZERO);
      typename Traits::Project project =
        (xz_plane) ? Traits::project_xz : Traits::project_yz;
      Direction_2 s = project(source);
      Direction_2 t = project(target);
      bool s_x_is_positive = is_x_positive(s);
      bool t_x_is_positive = is_x_positive(t);
      set_is_x_monotone(s_x_is_positive == t_x_is_positive);

      bool plane_is_positive = (xz_plane) ?
        (y_sign(normal) == NEGATIVE) : (x_sign(normal) == POSITIVE);
      bool ccw = ((plane_is_positive && s_x_is_positive) ||
                  (!plane_is_positive && !s_x_is_positive));
      this->set_is_directed_right(ccw);
      return;
    }
    
    // The arc is not vertical!
    this->set_is_vertical(false);
    Direction_2 s = Traits::project_xy(source);
    Direction_2 t = Traits::project_xy(target);
    Orientation orient = Traits::orientation(s, t);
    
    const Direction_2 & nx = Traits::neg_x_2();
    if (orient == LEFT_TURN) {
      this->set_is_directed_right(true);
      set_is_x_monotone(!kernel.counterclockwise_in_between_2_object()(nx, s, t));
      return;
    }        

    // (orient == RIGHT_TURN)
    this->set_is_directed_right(false);
    set_is_x_monotone(!kernel.counterclockwise_in_between_2_object()(nx, t, s));
    return;
  }

  /*! Construct a spherical_arc from two endpoint directions contained
   * in a plane.
   * \param plane the containing plane.
   * \param source the source-point direction.
   * \param target the target-point direction.
   * \pre Both endpoints lie on the given plane.
   */
  Arr_great_circular_arc_on_sphere_3(const Arr_extended_direction_3 & source,
                                     const Arr_extended_direction_3 & target,
                                     const Plane_3 & plane)
  {
    this->set_source(source);
    this->set_target(target);
    this->set_plane(plane);
    this->set_is_degenerate(false);

    typedef Arr_great_circular_arc_on_sphere_traits_2<Kernel> Traits;

    CGAL_precondition(this->has_on(plane, source));
    CGAL_precondition(this->has_on(plane, target));

    Direction_3 normal = plane.orthogonal_direction();
    if (z_sign(normal) == ZERO) {
      this->set_is_vertical(true);
    
      // Check whether both endpoint coincide with the poles:
      if (source.is_min_boundary() && target.is_max_boundary()) {
        // Both endpoints coincide with the 2 poles respectively.
        this->set_is_directed_right(true);
        this->set_is_full(false);
        set_is_x_monotone(true);
        return;
      }
      
      if (source.is_max_boundary() && target.is_min_boundary()) {
        // Both endpoints coincide with the 2 poles respectively.
        this->set_is_directed_right(false);
        this->set_is_full(false);
        set_is_x_monotone(true);
        return;
      }

      bool xz_plane = x_sign(normal) == ZERO;
      typename Traits::Project project =
        (xz_plane) ? Traits::project_xz : Traits::project_yz;
      Direction_2 s = project(source);
      Direction_2 t = project(target);
      bool s_x_is_positive = Traits::is_x_positive(s);
      bool t_x_is_positive = Traits::is_x_positive(t);
      bool plane_is_positive = (xz_plane) ?
        (y_sign(normal) == NEGATIVE) : (x_sign(normal) == POSITIVE);

      // Optimization:
      if (source.is_min_boundary()) {
        this->set_is_directed_right(true);
        set_is_x_monotone((plane_is_positive && t_x_is_positive) ||
                          (!plane_is_positive && !t_x_is_positive));
        return;
      }
      if (source.is_max_boundary()) {
        this->set_is_directed_right(false);
        set_is_x_monotone((plane_is_positive && !t_x_is_positive) ||
                          (!plane_is_positive && t_x_is_positive));
        return;
      }
      if (target.is_min_boundary()) {
        this->set_is_directed_right(false);
        set_is_x_monotone((plane_is_positive && !s_x_is_positive) ||
                          (!plane_is_positive && s_x_is_positive));
        return;
      }
      if (target.is_max_boundary()) {
        this->set_is_directed_right(true);
        set_is_x_monotone((plane_is_positive && s_x_is_positive) ||
                          (!plane_is_positive && !s_x_is_positive));
        return;
      }
      if (s_x_is_positive != t_x_is_positive) {
        set_is_x_monotone(false);
        return;
      }

      /* Non of the endpoints coincide with a pole.
       * The projections of both endpoints lie on the same hemi-circle.
       * Thus, either the arc is x-monotone, or it includes both poles.
       * This means that it is sufficient to check whether one pole lies
       * on the arc in order to determine x-monotonicity
       */
      const Direction_2 & ny = Traits::neg_y_2();
      Kernel kernel;
      typename Kernel::Counterclockwise_in_between_2 ccib =
        kernel.counterclockwise_in_between_2_object();
      set_is_x_monotone((plane_is_positive && !ccib(ny, s, t)) ||
                        (!plane_is_positive && !ccib(ny, t, s)));

      bool ccw = ((plane_is_positive && s_x_is_positive) ||
                  (!plane_is_positive && !s_x_is_positive));
      this->set_is_directed_right(ccw);
      return;
    }
      
    // The arc is not vertical!
    this->set_is_vertical(false);
    this->set_is_directed_right(z_sign(normal) == POSITIVE);
    const Direction_2 & nx = Traits::neg_x_2();
    Direction_2 s = Traits::project_xy(source);
    Direction_2 t = Traits::project_xy(target);    
    Kernel kernel;
    typename Kernel::Counterclockwise_in_between_2 ccib =
      kernel.counterclockwise_in_between_2_object();
    bool plane_is_positive = (z_sign(normal) == POSITIVE);
    set_is_x_monotone((plane_is_positive && !ccib(nx, s, t)) ||
                      (!plane_is_positive && !ccib(nx, t, s)));
  }

  /*! Construct a spherical_arc from two endpoints directions contained
   * in a plane.
   * \param plane the containing plane.
   * \param source the source-point direction.
   * \param target the target-point direction.
   * \pre The two endpoints are not the same, and both lie on the given plane.
   */
  Arr_great_circular_arc_on_sphere_3(const Plane_3 & plane)
  {
    this->set_plane(plane);
    typename Kernel::Direction_3 normal = plane.orthogonal_direction();
    this->set_is_vertical(CGAL::sign(normal.dz()) == ZERO);
    this->set_is_directed_right(true);
    this->set_is_full(true);
    this->set_is_degenerate(false);
    set_is_x_monotone(false);
  }

  /*! Indicates whether the arc is x-monotone
   * \return true if the arc is x-monotone; false otherwise
   */
  bool is_x_monotone() const { return m_is_x_monotone; }

  /*! Set the flag that indicates whether the arc is x-monotone
   * \param flag indicates whether the arc is x-monotone
   */
  void set_is_x_monotone(bool flag) { m_is_x_monotone = flag; }
};

/*! Inserter for the spherical_arc class used by the traits-class */
template <typename Kernel, typename OutputStream>
OutputStream & operator<<(OutputStream & os,
                          const Arr_extended_direction_3<Kernel> & ed)
{
  CGAL::To_double<typename Kernel::FT> todouble;
#if defined(CGAL_ARR_GREAT_CIRCULAR_ARC_ON_SPHERE_DETAILS)
  os << "(";
#endif
  os << static_cast<float>(todouble(ed.dx())) << ", "
     << static_cast<float>(todouble(ed.dy())) << ", "
     << static_cast<float>(todouble(ed.dz()));
#if defined(CGAL_ARR_GREAT_CIRCULAR_ARC_ON_SPHERE_DETAILS)
  os << ")"
     << ", "
     <<
    (ed.is_min_boundary() ? "min" :
     ed.is_max_boundary() ? "max" :
     ed.is_mid_boundary() ? "dis" : "reg");
#endif
  return os;
}

/*! Inserter for the spherical_arc class used by the traits-class */
template <typename Kernel, typename OutputStream>
OutputStream &
operator<<(OutputStream & os,
           const Arr_x_monotone_great_circular_arc_on_sphere_3<Kernel> & arc)
{
#if defined(CGAL_ARR_GREAT_CIRCULAR_ARC_ON_SPHERE_DETAILS)
  os << "(";
#endif
  os << "(" << arc.left() << "), (" << arc.right() << ")";
#if defined(CGAL_ARR_GREAT_CIRCULAR_ARC_ON_SPHERE_DETAILS)
  os << "("
     << ", " << (arc.is_vertical() ? " |" : "!|")
     << ", " << (arc.is_directed_right() ? "=>" : "<=");
#endif
  return os;
}

/*! Extractor for the spherical_arc class used by the traits-class */
template <typename Kernel, typename InputStream>
InputStream &
operator>>(InputStream & is,
           const Arr_x_monotone_great_circular_arc_on_sphere_3<Kernel> & arc)
{
  std::cerr << "Not implemented yet!" << std::endl;
  return is;
}  

CGAL_END_NAMESPACE

#endif
