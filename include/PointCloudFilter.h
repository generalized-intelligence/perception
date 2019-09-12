//
// Created by gishr on 2019/9/11.
//

#ifndef PERCEPTION_POINTCLOUDFILTER_H
#define PERCEPTION_POINTCLOUDFILTER_H

#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include <glog/logging.h>

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/filters/radius_outlier_removal.h>
#include <pcl/filters/conditional_removal.h>

#include <sensor_msgs/PointField.h>
#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/point_cloud_conversion.h>

#include <pcl_conversions/pcl_conversions.h>
#include <sensor_msgs/ChannelFloat32.h>
#include <sensor_msgs/PointField.h>

#include <geometry_msgs/Point32.h>
#include <opencv2/opencv.hpp>
#include <opencv2/ximgproc/disparity_filter.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/ximgproc.hpp"

namespace perception {


    class PointCloudFilter {

    public:

        EIGEN_MAKE_ALIGNED_OPERATOR_NEW

        PointCloudFilter();

        PointCloudFilter(std::string config_path);

        //PCL related pointcloud helper functions
        void ROSPointCloud2toPointCloudXYZ(sensor_msgs::PointCloud2& input_cloud, pcl::PointCloud<pcl::PointXYZ>& output_cloud);

        void PointCloudXYZtoROSPointCloud2(pcl::PointCloud<pcl::PointXYZ>& input_cloud, sensor_msgs::PointCloud2& output_cloud);

        sensor_msgs::PointField sensorPointField(std::string name_of_field, int offset, int datatype, int elementNum);

        bool createPointCloud2(std::vector<geometry_msgs::Point32>& input_points, sensor_msgs::PointCloud2& pc);

        //filters
        pcl::PointCloud<pcl::PointXYZ>::Ptr PCLStatisticalOutlierFilter(pcl::PointCloud<pcl::PointXYZ>::Ptr raw_cloud_p);

        pcl::PointCloud<pcl::PointXYZ>::Ptr PCLRadiusOutlierRemoval(pcl::PointCloud<pcl::PointXYZ>::Ptr raw_cloud_p);

        pcl::PointCloud<pcl::PointXYZ>::Ptr PCLConditionalRemoval(pcl::PointCloud<pcl::PointXYZ>::Ptr raw_cloud_p, float Min=0.0, float Max=3.0);

    private:

        pcl::StatisticalOutlierRemoval<pcl::PointXYZ> mStatisticalOutlierRemoval;
        pcl::RadiusOutlierRemoval<pcl::PointXYZ> mRadiusOutlierRemoval;

        std::string config_path;

        // for PCLRadiusOutlierRemoval
        float radius = 0.05;
        int MinNeighbor = 1;

        // for PCLStatisticalOutlierFilter
        int mean_k = 50;
        int stdThres = 1;
    };

}

#endif //PERCEPTION_POINTCLOUDFILTER_H
