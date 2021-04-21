# include <cstdio>
# include <cmath>
# include <iostream>
# include <string>
# include <vector>
# include <ctime>
# include <iomanip>
using namespace std; 

#include "omp.h"
int main(int argc, char *argv[]){
    char *flag = argv[1];
    char *numpoints = argv[2];
    char *numtrials = argv[3];
    char *dimension = argv[4];
    printf("Flag is %s \n",flag);
    printf("Number of points is %s \n",numpoints);
    printf("Number of trials is %s \n",numtrials);  
    int flag_val =atoi(flag);
    int V = atoi(numpoints);//convert string to int
    int num_trials = atoi(numtrials);
    int dim = atoi(dimension);
    float sum = 0;

    //timing
    time_t start = 0;
    time_t end = 0;
    double seconds;
    
    
    srand((unsigned) time (NULL));

    if(dim==0){
        printf("Zero dimension.\n");
        time(&start);
        //#pragma omp parallel for
        for(int t=0;t<num_trials;t++){

            //initialize vector that keeps vertex index in vec[i][0] and min weight in vec[i][1]
            vector<vector<float> > vec(V);
            for(int i =0;i<V;i++){
                float new_i = i*1.0;
                vec[i] = vector <float> {new_i,INFINITY};
                if(flag_val>2){
                    printf("index %d, vec[0] %.1f, vec[1] %f \n",i,vec[i][0],vec[i][1]);
                }
            }

            //pop the first vertex and initialize trial_sum and curr_index
            vec[0][1] = 0;
            vec.erase(vec.begin());
            float trial_sum = 0;
            int curr_index = 0; 

            while (vec.size()!=0){
                float min_weight = 2;
                for(int j = 0;j<vec.size();j++){
                    //initialize distance between vertices
                    float rand_val= ((float) rand() / (RAND_MAX));

                    if(flag_val>1){
                        printf("current vertex being explored %d, the neighbor is %0.1f which is reached from %d th edge original length %f", 
                        curr_index,vec[j][0],j,vec[j][1]);
                    }

                    if(rand_val <vec[j][1]){
                        //change min weight of v--w value if smaller weight is found
                        vec[j][1] = rand_val;
                    }

                    if(flag_val>1){
                        printf(" new length %f\n",vec[j][1]);
                    }
                    //update minimum distance
                    if (vec[j][1]<min_weight){
                        min_weight = vec[j][1];
                        curr_index = j;
                    }
                }
                if(flag_val){
                    printf("i %d temp min edge length %f\n",curr_index,min_weight);
                }
                trial_sum += min_weight;
                vec.erase(vec.begin()+curr_index);

            }
            cout<<"trial "<<t<<" sum: "<<trial_sum<<endl; 
            //printf("Hello from thread %d of %d. The value is %f\n",thread_num,max_thread,trial_sum);
            sum+=trial_sum;
        }

        time(&end);
    }
    else if (dim==1){
        time(&start);
        printf("One dimension is boring.\n");
        time(&end);

    }
        
    else if (dim==2){
        printf("Two dimension.\n");

        time(&start);
        //initialize coordinate
        for(int t = 0;t<num_trials;t++){
            vector<vector <float> > coordinate2D(V);
            
            //fill 2D-coordinate with values
            //#pragma omp parallel for
            for (int i=0;i<V;i++){
                float x_coordinate = ((float) rand() / (RAND_MAX));
                float y_coordinate = ((float) rand() / (RAND_MAX));
                
                coordinate2D[i] = vector<float> {x_coordinate,y_coordinate,INFINITY}; 

                if(flag_val>2){
                    printf("index %d, x_coord %.2f, y_coord %0.2f \n",i,coordinate2D[i][0],coordinate2D[i][1]);
                }      
            }

            //pop the first vertex and initialize trial_sum and curr_index
            vector<float> current_vertex = coordinate2D[0];
            coordinate2D[0][2] = 0;
            coordinate2D.erase(coordinate2D.begin());
            float trial_sum = 0;
            int curr_index = 0 ;


            //calculate distance
            while(coordinate2D.size()!=0){
                float min_weight = 2;

                for(int j=0;j<coordinate2D.size();j++){

                    //calculate Euclidean distance
                    float diff_x = coordinate2D[j][0]-current_vertex[0];
                    float diff_y = coordinate2D[j][1]-current_vertex[1];
                    float curr_dist = sqrt(pow(diff_x,2)+pow(diff_y,2));

                    if(flag_val>1){
                        printf("Exploring from V coord (%0.2f,%0.2f), W (%0.2f,%0.2f), original min weight %0.2f ",
                        current_vertex[0],current_vertex[1],coordinate2D[j][0],coordinate2D[j][1],coordinate2D[j][2]);
                    }

                    if (curr_dist<coordinate2D[j][2]){
                        coordinate2D[j][2] = curr_dist;
                    }

                    if(flag_val>1){
                        printf("curr weight is %0.2f,new edge length %0.2f\n",curr_dist,coordinate2D[j][2]);
                    }

                    //update minimum distance
                    if (coordinate2D[j][2] < min_weight){
                        min_weight = coordinate2D[j][2];
                        curr_index = j;
                    }
                
                }
                if(flag_val){
                    printf("next exploration from index %d whose min_edge length is %f\n",curr_index,min_weight);
                }
                current_vertex = {coordinate2D[curr_index][0],coordinate2D[curr_index][1]};
                coordinate2D.erase(coordinate2D.begin()+curr_index);
                trial_sum+=min_weight;

            }
            cout<<"trial "<<t<<" sum: "<<trial_sum<<endl; 
            sum+=trial_sum;
        }

        time(&end);
    }
    else if (dim==3){
        printf("Three dimension.\n");
        time(&start);

        //initialize coordinate
        for(int t = 0;t<num_trials;t++){
            vector<vector <float> > coordinate3D(V);
            
            //fill 2D-coordinate with values
            //#pragma omp parallel for
            for (int i=0;i<V;i++){
                float x_coordinate = ((float) rand() / (RAND_MAX));
                float y_coordinate = ((float) rand() / (RAND_MAX));
                float z_coordinate = ((float) rand() / (RAND_MAX));

                coordinate3D[i] = vector<float> {x_coordinate,y_coordinate,z_coordinate,INFINITY}; 

                if(flag_val>2){
                    printf("index %d, (%0.2f,%0.2f,%0.2f)\n",i,coordinate3D[i][0],coordinate3D[i][1],coordinate3D[i][2]);
                }
            }

            //pop the first vertex and initialize trial_sum and curr_index
            vector<float> current_vertex = coordinate3D[0];
            coordinate3D[0][3] = 0;
            coordinate3D.erase(coordinate3D.begin());
            float trial_sum = 0;
            int curr_index = 0 ;


            //calculate distance
            while(coordinate3D.size()!=0){
                float min_weight = 2;

                for(int j=0;j<coordinate3D.size();j++){

                    //calculate Euclidean distance
                    float diff_x = coordinate3D[j][0]-current_vertex[0];
                    float diff_y = coordinate3D[j][1]-current_vertex[1];
                    float diff_z = coordinate3D[j][2]-current_vertex[2];

                    float curr_dist = sqrt(pow(diff_x,2)+pow(diff_y,2)+pow(diff_z,2));

                    if(flag_val>1){
                        printf("Exploring from V coord (%0.2f,%0.2f,%0.2f), W (%0.2f,%0.2f,%0.2f), original min weight %0.2f ",
                        current_vertex[0],current_vertex[1],current_vertex[2],coordinate3D[j][0],coordinate3D[j][1],coordinate3D[j][2],coordinate3D[j][3]);
                    }

                    if (curr_dist<coordinate3D[j][3]){
                        coordinate3D[j][3] = curr_dist;
                    }

                    if(flag_val>1){
                        printf("curr weight is %0.2f,new edge length %0.2f\n",curr_dist,coordinate3D[j][3]);
                    }

                    //update minimum distance
                    if (coordinate3D[j][3] < min_weight){
                        min_weight = coordinate3D[j][3];
                        curr_index = j;
                    }
                
                }
                if(flag_val){
                    printf("next exploration from index %d whose min_edge length is %f\n",curr_index,min_weight);
                }
                current_vertex = {coordinate3D[curr_index]};
                coordinate3D.erase(coordinate3D.begin()+curr_index);
                trial_sum+=min_weight;

            }
            cout<<"trial "<<t<<" sum: "<<trial_sum<<endl; 
            sum+=trial_sum;
        }

        time(&end);
    }
    else if (dim==4){

        printf("Four dimension.\n");
        time(&start);

        //initialize coordinate
        for(int t = 0;t<num_trials;t++){
            vector<vector <float> > coordinate4D(V);
            
            //fill 2D-coordinate with values
            //#pragma omp parallel for
            for (int i=0;i<V;i++){
                float x_coordinate = ((float) rand() / (RAND_MAX));
                float y_coordinate = ((float) rand() / (RAND_MAX));
                float z_coordinate = ((float) rand() / (RAND_MAX));
                float w_coordinate = ((float) rand() / (RAND_MAX));

                coordinate4D[i] = vector<float> {x_coordinate,y_coordinate,z_coordinate,w_coordinate,INFINITY}; 

                if(flag_val>2){
                    printf("index %d, (%0.2f,%0.2f,%0.2f,%0.2f)\n",i,coordinate4D[i][0],coordinate4D[i][1],coordinate4D[i][2],coordinate4D[i][3]);
                }
            }

            //pop the first vertex and initialize trial_sum and curr_index
            vector<float> current_vertex = coordinate4D[0];
            coordinate4D[0][4] = 0;
            coordinate4D.erase(coordinate4D.begin());
            float trial_sum = 0;
            int curr_index = 0 ;

            //calculate distance
            while(coordinate4D.size()!=0){
                float min_weight = 2;

                for(int j=0;j<coordinate4D.size();j++){

                    //calculate Euclidean distance
                    float diff_x = coordinate4D[j][0]-current_vertex[0];
                    float diff_y = coordinate4D[j][1]-current_vertex[1];
                    float diff_z = coordinate4D[j][2]-current_vertex[2];
                    float diff_w = coordinate4D[j][3]-current_vertex[3];

                    float curr_dist = sqrt(pow(diff_x,2)+pow(diff_y,2)+pow(diff_z,2)+pow(diff_w,2));

                    if(flag_val>1){
                        printf("Exploring from V coord (%0.2f,%0.2f,%0.2f,%0.2f), W (%0.2f,%0.2f,%0.2f,%0.2f), original min weight %0.2f ",
                        current_vertex[0],current_vertex[1],current_vertex[2],current_vertex[3],coordinate4D[j][0],coordinate4D[j][1],coordinate4D[j][2],coordinate4D[j][3],coordinate4D[j][4]);
                    }

                    if (curr_dist<coordinate4D[j][4]){
                        coordinate4D[j][4] = curr_dist;
                    }

                    if(flag_val>1){
                        printf("curr weight is %0.2f,new edge length %0.2f\n",curr_dist,coordinate4D[j][4]);
                    }

                    //update minimum distance
                    if (coordinate4D[j][4] < min_weight){
                        min_weight = coordinate4D[j][4];
                        curr_index = j;
                    }
                
                }
                if(flag_val){
                    printf("next exploration from index %d whose min_edge length is %f\n",curr_index,min_weight);
                }
                current_vertex = {coordinate4D[curr_index]};
                coordinate4D.erase(coordinate4D.begin()+curr_index);
                trial_sum+=min_weight;

            }
            cout<<"trial "<<t<<" sum: "<<trial_sum<<endl; 
            sum+=trial_sum;
        }

        time(&end);
    }
    else{
        printf("Enter correct dimension");
    }


    cout<<"average sum: "<<sum/num_trials<<endl; 
    seconds=difftime(end,start);
    printf ("%.f seconds during operation.\n", seconds);

}
