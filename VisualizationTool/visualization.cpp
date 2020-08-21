//
// Created by chumen on 2020/8/20.
//
#include<iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/utils/filesystem.hpp>
#include <stdio.h>
#include <string>
#include <dirent.h>

#define WIDTH 640
#define HEIGHT 480
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define YELLOW  "\033[33m"      /* Yellow */
using namespace std;
/*递归读取binfile文件夹下面所有的.bin文件
并且创建好可视化后png保存的目录*/
bool GetBinfilesPath(string father_dir, vector<string> &binfiles ){
    DIR *dir=opendir(father_dir.c_str());
    if(dir==NULL){
        cout << father_dir << " don't exit!" << endl;
        return false;
    }
    struct dirent *entry;
    while((entry = readdir(dir)) != NULL){
        string name(entry->d_name);
        // 类型为目录                    排除“.”和“..”以及隐藏文件夹
        if(entry->d_type == DT_DIR ) {
            if (name.find(".") == string::npos) {
                string son_dir = father_dir + name + "/";

                //创建png的目录
                string png_son_dir = son_dir;
                string mkdir = "mkdir -p " + png_son_dir.replace(png_son_dir.find("bin"), 3, "png");
                cout << mkdir << endl;
                system(mkdir.c_str());

                vector<string> tempPath;
                GetBinfilesPath(son_dir, tempPath);
                binfiles.insert(binfiles.end(), tempPath.begin(), tempPath.end());
            }
        }
        // 类型为目录。只找bin文件
        else if(name.find("bin") != string::npos)
            binfiles.push_back(father_dir+name);
    }
    closedir(dir);
    return true;
}

int main() {
    string binfile_dir = "../binfile/";
    vector<string> binfiles;
    GetBinfilesPath(binfile_dir,binfiles);
    FILE *fp;

    for (int i = 0; i < binfiles.size(); i++) {
        cout << RED << "Reading: "<< RESET << binfiles[i] << endl;
        fp = fopen(binfiles[i].c_str(), "r");

        /*读取文件*/
        uint16_t depth[WIDTH * HEIGHT] = {0};
        //memset(depth,0,sizeof(depth));
        fread(depth, sizeof(uint16_t), WIDTH * HEIGHT, fp);

        /*可以将深度值的最大最小值归一化到0-255，也可以固定将0mm-7500mm归一化到0-255。*/
        // 7500是因为在ipad上保存的时候，将7500mm设置成了深度值的上限，以免噪声的值大于uint16的取值范围
        //uint16_t max_depth = 7500;
        //uint16_t min_depth = 0;
        uint16_t max_depth = *max_element(depth, depth + WIDTH * HEIGHT);
        uint16_t min_depth = *min_element(depth, depth + WIDTH * HEIGHT);
        double temp = (double)255 / (max_depth - min_depth);

        /*生成深度图*/
        cv::Mat depthmap = cv::Mat::zeros(HEIGHT, WIDTH, CV_8UC1);
        for (int i = 0; i < WIDTH * HEIGHT; i++) {
            depthmap.at<uchar>(i/WIDTH,i%WIDTH) = depth[i] * temp;
            //cout << i<< " " << depth[i] << " " <<(int)depthmap.at<uchar>(i/WIDTH,i%WIDTH) <<endl ;
        }

        /*显示*/
        //cv::imshow("test", depthmap);
        //cv::waitKey();

        /*保存*/
        string imagefile=binfiles[i].replace(binfiles[i].find("bin"),3,"png");
        imagefile=imagefile.replace(imagefile.find("bin"),3,"png"); // 将两个“bin”都替换成“png”
        cout << YELLOW <<"Saving: " << RESET <<imagefile << endl;
        cv::imwrite(imagefile,depthmap);

        fclose(fp);
    }

    return 0;
}
