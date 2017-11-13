#ifndef PATH_CALCULATOR_H
#define PATH_CALCULATOR_H
#include <cmath>
#include <misc_math.h>
#include <opencv2/opencv.hpp>
#include <renderable.h>
#include <tinysplinecpp.h>
#include <vector>
#include <socket.h>
/*
 * TODO: Make an interface class for path calculators, this one only works
 * with tank drive controls
 * TODO: Make PathCalculator inherit from Renderable
 */

class Path : public Renderable {
	public:
		struct PrimitivePoint {
			float position;
			float velocity;
		};
		struct TalonPoint {
			cv::Point2f display_point;
			PrimitivePoint primitive;
			TalonPoint(float position, float velocity, cv::Point2f display_point)
			{
				this->display_point = display_point;
				primitive.position = position;
				primitive.velocity = velocity;
			}
			TalonPoint(PrimitivePoint* primitive, cv::Point2f display_point) {
				this->display_point = display_point;
				this->primitive = *primitive;
			}
		};

		//A serializable non-opencv dependent version of TalonPoint

		const float pi = acos(-1);
		std::vector<TalonPoint> path_left;
		std::vector<TalonPoint> path_right;
		Path(tinyspline::BSpline* spline, float wheel_distance, float step);
		Path(Socket* sock);
		void render();
		cv::Rect2f get_size();
		void color_by(float input);
		void to_socket (Socket* sock);
		void from_socket (Socket* sock);
};
#endif
