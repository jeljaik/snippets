#include <iostream>
#include <cmath>
#include <Eigen/Geometry>
#include <Eigen/Core>

using namespace std;

///////////////////////////////
// Quaternion struct
// Simple incomplete quaternion struct for demo purpose
///////////////////////////////
struct Quaternion{
    Quaternion():x(0), y(0), z(0), w(1){};
    Quaternion(double x, double y, double z, double w):x(x), y(y), z(z), w(w){};
    
    void normalize(){
        double norm = std::sqrt(x*x + y*y + z*z + w*w);
        x /= norm;
        y /= norm;
        z /= norm;
        w /= norm;
    }
    
    double norm(){
        return std::sqrt(x*x + y*y + z*z + w*w);
    }
    
    double x;
    double y;
    double z;
    double w;
    
};

///////////////////////////////
// Quaternion to Euler
///////////////////////////////
enum RotSeq{zyx, zyz, zxy, zxz, yxz, yxy, yzx, yzy, xyz, xyx, xzy,xzx};

void twoaxisrot(double r11, double r12, double r21, double r31, double r32, double res[]){
    res[0] = atan2( r11, r12 );
    res[1] = acos ( r21 );
    res[2] = atan2( r31, r32 );
}

void threeaxisrot(double r11, double r12, double r21, double r31, double r32, double res[]){
    res[0] = atan2( r31, r32 );
    res[1] = asin ( r21 );
    res[2] = atan2( r11, r12 );
}

void quaternion2Euler(const Quaternion& q, double res[], RotSeq rotSeq)
{
    switch(rotSeq){
        case zyx:
            threeaxisrot( 2*(q.x*q.y + q.w*q.z),
                         q.w*q.w + q.x*q.x - q.y*q.y - q.z*q.z,
                         -2*(q.x*q.z - q.w*q.y),
                         2*(q.y*q.z + q.w*q.x),
                         q.w*q.w - q.x*q.x - q.y*q.y + q.z*q.z,
                         res);
            break;
            
        case zyz:
            twoaxisrot( 2*(q.y*q.z - q.w*q.x),
                       2*(q.x*q.z + q.w*q.y),
                       q.w*q.w - q.x*q.x - q.y*q.y + q.z*q.z,
                       2*(q.y*q.z + q.w*q.x),
                       -2*(q.x*q.z - q.w*q.y),
                       res);
            break;
            
        case zxy:
            threeaxisrot( -2*(q.x*q.y - q.w*q.z),
                         q.w*q.w - q.x*q.x + q.y*q.y - q.z*q.z,
                         2*(q.y*q.z + q.w*q.x),
                         -2*(q.x*q.z - q.w*q.y),
                         q.w*q.w - q.x*q.x - q.y*q.y + q.z*q.z,
                         res);
            break;
            
        case zxz:
            twoaxisrot( 2*(q.x*q.z + q.w*q.y),
                       -2*(q.y*q.z - q.w*q.x),
                       q.w*q.w - q.x*q.x - q.y*q.y + q.z*q.z,
                       2*(q.x*q.z - q.w*q.y),
                       2*(q.y*q.z + q.w*q.x),
                       res);
            break;
            
        case yxz:
            threeaxisrot( 2*(q.x*q.z + q.w*q.y),
                         q.w*q.w - q.x*q.x - q.y*q.y + q.z*q.z,
                         -2*(q.y*q.z - q.w*q.x),
                         2*(q.x*q.y + q.w*q.z),
                         q.w*q.w - q.x*q.x + q.y*q.y - q.z*q.z,
                         res);
            break;
            
        case yxy:
            twoaxisrot( 2*(q.x*q.y - q.w*q.z),
                       2*(q.y*q.z + q.w*q.x),
                       q.w*q.w - q.x*q.x + q.y*q.y - q.z*q.z,
                       2*(q.x*q.y + q.w*q.z),
                       -2*(q.y*q.z - q.w*q.x),
                       res);
            break;
            
        case yzx:
            threeaxisrot( -2*(q.x*q.z - q.w*q.y),
                         q.w*q.w + q.x*q.x - q.y*q.y - q.z*q.z,
                         2*(q.x*q.y + q.w*q.z),
                         -2*(q.y*q.z - q.w*q.x),
                         q.w*q.w - q.x*q.x + q.y*q.y - q.z*q.z,
                         res);
            break;
            
        case yzy:
            twoaxisrot( 2*(q.y*q.z + q.w*q.x),
                       -2*(q.x*q.y - q.w*q.z),
                       q.w*q.w - q.x*q.x + q.y*q.y - q.z*q.z,
                       2*(q.y*q.z - q.w*q.x),
                       2*(q.x*q.y + q.w*q.z),
                       res);
            break;
            
        case xyz:
            threeaxisrot( -2*(q.y*q.z - q.w*q.x),
                         q.w*q.w - q.x*q.x - q.y*q.y + q.z*q.z,
                         2*(q.x*q.z + q.w*q.y),
                         -2*(q.x*q.y - q.w*q.z),
                         q.w*q.w + q.x*q.x - q.y*q.y - q.z*q.z,
                         res);
            break;
            
        case xyx:
            twoaxisrot( 2*(q.x*q.y + q.w*q.z),
                       -2*(q.x*q.z - q.w*q.y),
                       q.w*q.w + q.x*q.x - q.y*q.y - q.z*q.z,
                       2*(q.x*q.y - q.w*q.z),
                       2*(q.x*q.z + q.w*q.y),
                       res);
            break;
            
        case xzy:
            threeaxisrot( 2*(q.y*q.z + q.w*q.x),
                         q.w*q.w - q.x*q.x + q.y*q.y - q.z*q.z,
                         -2*(q.x*q.y - q.w*q.z),
                         2*(q.x*q.z + q.w*q.y),
                         q.w*q.w + q.x*q.x - q.y*q.y - q.z*q.z,
                         res);
            break;
            
        case xzx:
            twoaxisrot( 2*(q.x*q.z - q.w*q.y),
                       2*(q.x*q.y + q.w*q.z),
                       q.w*q.w + q.x*q.x - q.y*q.y - q.z*q.z,
                       2*(q.x*q.z + q.w*q.y),
                       -2*(q.x*q.y - q.w*q.z),
                       res);
            break;
        default:
            std::cout << "Unknown rotation sequence" << std::endl;
            break;
    }
}

///////////////////////////////
// Helper functions
///////////////////////////////
Quaternion operator*(Quaternion& q1, Quaternion& q2){
    Quaternion q;
    q.w = q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z;
    q.x = q1.w*q2.x + q1.x*q2.w + q1.y*q2.z - q1.z*q2.y;
    q.y = q1.w*q2.y - q1.x*q2.z + q1.y*q2.w + q1.z*q2.x;
    q.z = q1.w*q2.z + q1.x*q2.y - q1.y*q2.x + q1.z*q2.w;
    return q;
}

std::ostream& operator <<(std::ostream& stream, const Quaternion& q) {
//    cout << q.w << " "<< showpos << q.x << "i " << q.y << "j " << q.z << "k";
//    cout << noshowpos;
    
    std::ostringstream s;
    s << q.w << " " << q.x << " " << q.y << " " << q.z;
    std::string tmp = s.str();
    return stream << tmp;
}

double rad2deg(double rad){
    return rad*180.0/M_PI;
}

double deg2rad(double deg){
    return deg*M_PI/180;
}

void compareWithEigen( double rotX, double rotY, double rotZ )
{
    cout << "Rotating first [" << rad2deg(rotZ) << " around Z] " << " -> [" << rad2deg(rotY) << " around Y] " << " -> [" << rad2deg(rotX) << " around X] " << endl;
    // MANUAL COMPUTATIONS
    // Elementary quaternion rotations
    Quaternion qx(sin(rotX/2), 0, 0, cos(rotX/2));
    Quaternion qy(0, sin(rotY/2), 0, cos(rotY/2));
    Quaternion qz(0, 0, sin(rotZ/2), cos(rotZ/2));
    cout << "Rotation sequence will be: Z->Y->X" << endl;
    Quaternion q = qy*qz; q = qx*q;
    q.normalize();
    // Result of quaternion2Euler
    double res[3];
    Eigen::Matrix3d auxMat;
    Eigen::Vector3d eulerEigen;
    // For the order of rotations Z->Y->X quaternion2Euler is passed zyx
    quaternion2Euler(q, res, xyz);
    cout << "Manual Quaternion for this orientation: " << q << endl;
    cout << "Manually Computed Euler Angles: " << endl;
    cout << "x (roll): " << rad2deg(res[0]) << " y (pitch): " << rad2deg(res[1]) << " z (yaw): " << rad2deg(res[2]) << endl;
    
    // EIGEN COMPUTATIONS
    Eigen::Quaterniond qEigen;
    qEigen.w() = q.w;
    qEigen.x() = q.x;
    qEigen.y() = q.y;
    qEigen.z() = q.z;
    cout << "Eigen quaternion: " << qEigen.w() << " " << qEigen.x() << " " << qEigen.y() << " " << qEigen.z() << endl;
//    Eigen::AngleAxisd rollAngle(rotX, Eigen::Vector3d::UnitX());
//    Eigen::AngleAxisd pitchAngle(rotY, Eigen::Vector3d::UnitY());
//    Eigen::AngleAxisd yawAngle(rotZ, Eigen::Vector3d::UnitZ());
    // For the order of rotations Z->Y->X quaternion2Euler is passed zyx
//    qEigen = rollAngle * pitchAngle * yawAngle;
    auxMat = qEigen.toRotationMatrix();
    eulerEigen = auxMat.eulerAngles(0, 1, 2);
    cout << "Eigen computed Euler Angles: " << endl;
    cout << "x (roll): " << rad2deg(eulerEigen[0]) << " y (pitch): " << rad2deg(eulerEigen[1]) << " z (yaw): " << rad2deg(eulerEigen[2]) << endl;
    
    cout << "Rotation matrix from passed rotations: " << endl;
    Eigen::Matrix3f m;
    m = Eigen::AngleAxisf(rotX, Eigen::Vector3f::UnitX())
      * Eigen::AngleAxisf(rotY, Eigen::Vector3f::UnitY())
      * Eigen::AngleAxisf(rotZ, Eigen::Vector3f::UnitZ());
    cout << m << endl;
    
    cout << "Rotation matrix from Eigen quaternion: " << endl;
    cout << auxMat << endl << endl;
    
    cout << "Rotation matrix from eulerAngles 0 1 2: " << endl;
    m = Eigen::AngleAxisf(eulerEigen[0], Eigen::Vector3f::UnitX())
      * Eigen::AngleAxisf(eulerEigen[1], Eigen::Vector3f::UnitY())
      * Eigen::AngleAxisf(eulerEigen[2], Eigen::Vector3f::UnitZ());
    cout << m << endl;
    
    double tol = 1e-5;
    if ( (eulerEigen[0] - rotX) < tol && (eulerEigen[1] - rotY) < tol && (eulerEigen[2] - rotZ) < tol )
    {
        cout << "The (Eigen) Euler angles from the quaternion produced by the specified rotations are as expected " << endl << endl;
    }


}

///////////////////////////////
// Main
///////////////////////////////
int main(){
    
    Quaternion q; // x,y,z,w
    Quaternion qx45(sin(M_PI/8), 0,0, cos(M_PI/8) );
    Quaternion qy45(0, sin(M_PI/8), 0, cos(M_PI/8));
    Quaternion qz45(0, 0, sin(M_PI/8), cos(M_PI/8));
    Quaternion qx90(sin(M_PI/4), 0,0, cos(M_PI/4) );
    Quaternion qy90(0, sin(M_PI/4), 0, cos(M_PI/4));
    Quaternion qz90(0, 0, sin(M_PI/4), cos(M_PI/4));
    Quaternion qx30(sin(M_PI/12), 0, 0, cos(M_PI/12));
    
    Eigen::Matrix3d auxMat;
    double rollDeg  = 30;
    double pitchDeg = 30;
    double yawDeg   = 30;
    
    // Tests using function compareWithEigen
    // rolDeg Rotation about x
    compareWithEigen((M_PI/180)*rollDeg, 0, 0);
    // pitchDeg rotation about y
    compareWithEigen(0, (M_PI/180)*pitchDeg, 0);
    // yawDeg rotation about z
    compareWithEigen(0, 0, (M_PI/180)*yawDeg);
    
    // Two rotations
    compareWithEigen(deg2rad(20), deg2rad(20), 0);
    
    // Three rotations
    compareWithEigen(deg2rad(10), deg2rad(30), deg2rad(40));

    
    
    
    
    
    
    
    // Rotation of 45 deg around x
//    q = qx45; rollDeg = 45; pitchDeg = 0; yawDeg = 0;
//    q.normalize();
//    quaternion2Euler(q, res, zyx);
//    cout << "Rotation sequence: X->Y->Z" << endl;
//    cout << "x45 -> I -> I" << endl;
//    cout << "q: " << q << endl;
//    cout << "Manual: " << endl;
//    cout << "x: " << rad2deg(res[0]) << " y: " << rad2deg(res[1]) << " z: " << rad2deg(res[2]) << endl << endl;
//    Eigen::Quaterniond qx45Eigen;
//    qx45Eigen.w() = cos((M_PI/8));
//    qx45Eigen.x() = sin(M_PI/8);
//    qx45Eigen.y() = 0;
//    qx45Eigen.z() = 0;
//    Eigen::Matrix3d rotEigen = qx45Eigen.toRotationMatrix();
//    Eigen::Vector3d eulerEigen = rotEigen.eulerAngles(0, 1, 2);
//    cout << "Euler Angles from Eigen: " << rad2deg(eulerEigen(0)) << " " << rad2deg(eulerEigen(1)) << " " << rad2deg(eulerEigen(2)) << endl << endl;
//    
//    // Rotation of 45 deg around y
//    q = qy45;
//    q.normalize();
//    quaternion2Euler(q, res, zyx);
//    cout << "Rotation sequence: X->Y->Z" << endl;
//    cout << "I -> y45 -> I" << endl;
//    cout << "q: " << q << endl;
//    cout << "Manual: " << endl;
//    cout << "x: " << rad2deg(res[0]) << " y: " << rad2deg(res[1]) << " z: " << rad2deg(res[2]) << endl << endl;
//
//    // Rotation of 45 deg around z
//    q = qz45;
//    q.normalize();
//    quaternion2Euler(q, res, zyx);
//    cout << "Rotation sequence: X->Y->Z" << endl;
//    cout << "I -> I -> z45" << endl;
//    cout << "q: " << q << endl;
//    cout << "Manual: " << endl;
//    cout << "x: " << rad2deg(res[0]) << " y: " << rad2deg(res[1]) << " z: " << rad2deg(res[2]) << endl << endl;
//
//    
//    
//    
//    
//    q = qz45*qx45;
//    q.normalize();
//    quaternion2Euler(q, res, zyx);
//    cout << "Rotation sequence: X->Y->Z" << endl;
//    cout << "x45 -> z45" << endl;
//    cout << "q: " << q << endl;
//    cout << "x: " << rad2deg(res[0]) << " y: " << rad2deg(res[1]) << " z: " << rad2deg(res[2]) << endl << endl;
//    
//    // Same rotation through Eigen
////    Eigen::Quaternion<double> qEigen
//    cout << "Rotation sequence Eigen: X->Y->Z" << endl;
//    double roll = (M_PI/180)*45;
//    double yaw = (M_PI/180)*45;
//    double pitch = 0;
//    Eigen::AngleAxisd rollAngle(roll, Eigen::Vector3d::UnitX());
//    Eigen::AngleAxisd pitchAngle(pitch, Eigen::Vector3d::UnitY());
//    Eigen::AngleAxisd yawAngle(yaw, Eigen::Vector3d::UnitZ());
//    
//    Eigen::Quaterniond qEigen = yawAngle * pitchAngle * rollAngle;
//    qEigen.normalize();
//    cout << "Eigen Quaternion " << qEigen.w() << " " << qEigen.x() << " " << qEigen.y() << " " << qEigen.z() << " " << endl;
//    Eigen::Matrix3d m = qEigen.toRotationMatrix();
//    Eigen::Vector3d eulEigen = m.eulerAngles(2, 1, 0);
//    
//    cout << "Euler Angles from Eigen: " << rad2deg(eulEigen(0)) << " " << rad2deg(eulEigen(1)) << " " << rad2deg(eulEigen(2)) << endl << endl;
//    
//
//    // Testing 45 deg rotation about Z, then Y, then X  (i.e. xyz)
//    q = qy45*qz45;
//    q = qx30*q;
//    q.normalize();
//    quaternion2Euler(q, res, xyz);
//    cout << "Rotation sequence: Z->Y->X" << endl;
//    cout << "z45 -> y45 -> x45" << endl;
//    cout << "q: " << q << endl;
//    cout << "x(roll): " << rad2deg(res[0]) << " y(pitch): " << rad2deg(res[1]) << " z(yaw): " << rad2deg(res[2]) << endl;
//    
//    //Testing 45 deg rotation about z, then y, then x (i.e. 012) with Eigen
//    roll = (M_PI/180)*30;
//    pitch = (M_PI/180)*45;
//    yaw = (M_PI/180)*45;
//    Eigen::AngleAxisd rollAngle2(roll, Eigen::Vector3d::UnitX());
//    Eigen::AngleAxisd pitchAngle2(pitch, Eigen::Vector3d::UnitY());
//    Eigen::AngleAxisd yawAngle2(yaw, Eigen::Vector3d::UnitZ());
//    
//    qEigen = rollAngle2 * pitchAngle2 * yawAngle2;
//    qEigen.normalize();
//    cout << "Eigen Quaternion " << qEigen.w() << " " << qEigen.x() << " " << qEigen.y() << " " << qEigen.z() << " " << endl;
//    m = qEigen.toRotationMatrix();
//    eulEigen = m.eulerAngles(0, 1, 2);
//    cout << "Euler Angles from Eigen: " << rad2deg(eulEigen(0)) << " " << rad2deg(eulEigen(1)) << " " << rad2deg(eulEigen(2)) << endl << endl;
//    
//                                                    
//    // Testing a single quaternion from wholeBodyEstimator
////    Quaternion qTest(0.014728, -0.00823561, 0.306346, 0.951771);
//    Quaternion qTest (0.016998, -0.00716782, 0.32524, 0.945452);
//    cout << "Hardcoded normal quaternion: (w): " << qTest.w << " (x): " << qTest.x << " (y): " << qTest.y << " (z):" << qTest.z << endl;
////    qTest.normalize();
//    quaternion2Euler(qTest, res, xyz);
//    cout << "Rotation sequence: Z->Y->X" << endl;
//    cout << "Euler from manual computation: x(roll): " << rad2deg(res[0]) << " y(pitch): " << rad2deg(res[1]) << " z(yaw): " << rad2deg(res[2]) << endl;
//    // With Eigen
//    cout << "The corresponding Eigen quaternion would be: " << endl;
//    roll = res[0];
//    pitch = res[1];
//    yaw = res[2];
//    Eigen::AngleAxisd rollAngle3(roll, Eigen::Vector3d::UnitX());
//    Eigen::AngleAxisd pitchAngle3(pitch, Eigen::Vector3d::UnitY());
//    Eigen::AngleAxisd yawAngle3(yaw, Eigen::Vector3d::UnitZ());
//    qEigen = rollAngle3 * pitchAngle3 * yawAngle3;
//    qEigen.w() = 0.945452;
//    qEigen.x() = 0.016998;
//    qEigen.y() = -0.00716782;
//    qEigen.z() = 0.32524;
//    cout << "Eigen Quaternion " << qEigen.w() << " " << qEigen.x() << " " << qEigen.y() << " " << qEigen.z() << " " << endl;
//    m = qEigen.toRotationMatrix();
//    eulEigen = m.eulerAngles(0, 1, 2);
//    cout << "Euler Angles from Eigen: x(roll): " << rad2deg(eulEigen(2)) << " y(pitch): " << rad2deg(eulEigen(1)) << " z(yaw) " << rad2deg(eulEigen(0)) << endl << endl;
//
//    
//    
//
//    q = qz90*qx90;
//    q.normalize();
//    quaternion2Euler(q, res, zyx);
//    cout << "Rotation sequence: X->Y->Z" << endl;
//    cout << "x90 -> z90" << endl;
//    cout << "q: " << q << endl;
//    cout << "x: " << rad2deg(res[0]) << " y: " << rad2deg(res[1]) << " z: " << rad2deg(res[2]) << endl << endl;
//    
//    q = qx90*qz90;
//    q.normalize();
//    quaternion2Euler(q, res, xyz);
//    cout << "Rotation sequence: Z->Y->X" << endl;
//    cout << "z90 -> x90" << endl;
//    cout << "q: " << q << endl;
//    cout << "x: " << rad2deg(res[0]) << " y: " << rad2deg(res[1]) << " z: " << rad2deg(res[2]) << endl;
}
