#include <iostream>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/adapted/boost_tuple.hpp>
#include <Eigen/Core>

BOOST_GEOMETRY_REGISTER_BOOST_TUPLE_CS(cs::cartesian)

int main()
{
    Eigen::MatrixXd feetCoords(8,2);
    feetCoords << 1, 1,
                    1, 2,
                    2, 2,
                    2, 1,
                    3, 3,
                    4, 3,
                    4, 4,
                    3, 4;

    typedef boost::tuple<double, double> point;
    typedef boost::geometry::model::polygon<point> polygon;

    polygon poly;

    for (unsigned int i=0 ; i<feetCoords.rows(); i++) {
        poly.outer().push_back(point(feetCoords(i,0), feetCoords(i,1)));
    }

    polygon hull;
    boost::geometry::convex_hull(poly, hull);

    using boost::geometry::dsv;
    std::cout
    << "polygon: " << dsv(poly) << std::endl
    << "hull: " << dsv(hull) << std::endl
    ;


    return 0;
}
