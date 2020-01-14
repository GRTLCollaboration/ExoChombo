/* GRChombo
 * Copyright 2012 The GRChombo collaboration.
 * Please refer to LICENSE in GRChombo's root directory.
 */

#ifndef CYLINDRICALGEOMETRY_HPP_
#define CYLINDRICALGEOMETRY_HPP_

#include "SurfaceGeometry.hpp"
#include <array>
#include <cmath>

//! This class, derived from the SurfaceGeometry class, provides cylindrical shell
//! geometry implementation for the SurfaceExtraction class
//! v = phi
class CylindricalGeometry : public SurfaceGeometry
{
  private:
    std::array<double, CH_SPACEDIM> m_center;
    double m_z_length;

  public:
    CylindricalGeometry(std::array<double, CH_SPACEDIM> &a_center, double &a_z_length)
      : m_center(a_center), m_z_length(a_z_length)
    {
    }

    //! returns the grid spacing in z
    virtual double du(int a_num_points_z) const override
    {
      return m_z_length / (a_num_points_z - 1);
    }

    //! returns the grid spacing in phi
    virtual double dv(int a_num_points_phi) const override
    {
      return 2.0 * M_PI / ((double)a_num_points_phi);
    }

    //! returns the z coordinate associated to the theta/u index
    virtual double u(int a_iz, int a_num_points_z) const override
    {
      return a_iz * du(a_num_points_z) - (m_z_length / 2.0);
    }

    //! returns the phi coordinate associated to the phi/v index
    virtual double v(int a_iphi, int a_num_points_phi) const override
    {
        return a_iphi * dv(a_num_points_phi);
    }

    virtual bool is_u_periodic() const override { return false; }
    virtual bool is_v_periodic() const override { return true; }
    //! returns the Cartesian coordinate in direction a_dir with specified
    //! radius, z and phi.
    virtual double cartesian_coord(int a_dir, double a_radius, double a_z,
                                   double a_phi) const override
    {
        switch (a_dir)
        {
        case (0):
            return m_center[0] + a_radius * cos(a_phi);
        case (1):
            return m_center[1] + a_radius * sin(a_phi);
        case (2):
            return m_center[2] + a_z;
        default:
            MayDay::Error("CylindricalGeometry: Direction not supported");
        }
    }

    //! returns the area element on a cylinder with radius a_radius at the point
    //! (a_z, a_phi)
    virtual double area_element(double a_radius, double a_z,
                                double a_phi) const override
    {
        return a_radius;
    }

    virtual std::string param_name() const override { return "r"; }

    virtual std::string u_name() const override { return "z"; }

    virtual std::string v_name() const override { return "phi"; }
};

#endif /* CYLINDRICALGEOMETRY_HPP_ */
