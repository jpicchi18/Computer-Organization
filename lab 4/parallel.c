//OpenMP version.  Edit and submit only this file.
/* Enter your details below
 * Name : Joseph Picchi
 * UCLA ID : 605124511
 * Email : jpicchi22@g.ucla.edu
 */

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#include "utils.h"

double work_it_par(long *old, long *new, long *super, long *simple, long *fibonacci) {
  int i, j, k;
  int u, v, w;
  int ton = 0;
  long compute_it, moving_average;
  double pi, pi2, x , y, sum, step = 0.0;
  long dot_product=0;
  long nCirc=0;
  long aggregate=1.0;
  double r=1.0;
  int was_smart = 16;

  for(i=0; i<DIM-1;i++)
  {
    super[i] += simple[i];
  }

  for(i=0; i<DIM-1;i++)
  {
    dot_product += super[i]*simple[i];
    
    moving_average = 0;
    for(ton=i;ton<DIM-1-WINDOW_SIZE;ton++)
    {
      moving_average += simple[ton];
    }
  }

 
  int a_secret = 5;
  fibonacci[0] = 1;
  fibonacci[1] = 1;
  printf("\n A secret is: %d",obfuscate_obfuscate_obfuscate(a_secret));
  
  for(i=2; i<DIM-1;i++)
    {
      fibonacci[i]=fibonacci[i-1]+fibonacci[i-2];
    }


  step = 1.0 / NUM_STEPS;
  
  omp_set_num_threads(omp_get_num_procs());
#pragma omp parallel for private(i, x) reduction(+: sum)
  for (i=0;i<NUM_STEPS; i++)
  {
    x = (i+0.5)*step;
    sum = sum + 4.0/(1.0+x*x);
  }
  pi = step * sum;
  printf("\n %d trials, Riemann flavored pi is %f \n",NUM_STEPS, pi); 
  
  for(i=0;i<NUM_TRIALS; i++)
  {
    x = (random()%10000000)/10000000.0; 
    y = (random()%10000000)/10000000.0;
    if (( x*x + y*y) <= r*r) {
      nCirc++;
    }
  } 
  pi2 = 4.0 * ((double)nCirc/(double)NUM_TRIALS);
  printf("\n %d trials, Monte-Carlo flavored pi is %f \n",NUM_TRIALS, pi2); 

  int we_need_val = we_need_the_func();
  int gimmie_val = gimmie_the_func();
#pragma omp parallel for collapse(3) private(i, j, k, compute_it)	\
  reduction(+: aggregate)
  for (i=1; i<DIM-1; i++) {
    for (j=1; j<DIM-1; j++) {
      for (k=1; k<DIM-1; k++) {
        compute_it = old[i*DIM*DIM+j*DIM+k] * we_need_val;
        aggregate+= compute_it / gimmie_val;
      }
    }
  }

  printf("AGGR:%ld\n",aggregate);


  int temp;
  #pragma omp parallel
  {
#pragma omp for collapse(3) private(i, j, k, u, v, w, temp)
  for (i=1; i<DIM-1; i++) {
    for (j=1; j<DIM-1; j++) {
      for (k=1; k<DIM-1; k++) {
	temp=0;
        for (u=-1; u<=1; u++) {
          for (v=-1; v<=1; v++) {
            for (w=-1; w<=1; w++) {
	      temp+=old[(i+u)*DIM*DIM+(j+v)*DIM+(k+w)];
            }
          }
        }
	new[i*DIM*DIM+j*DIM+k]=temp/27;
      }
    }
  }
  } 


  for (i=1; i<DIM-1; i++) {
    for (j=1; j<DIM-1; j++) {
      for (k=1; k<DIM-1; k++) {
        u=(new[i*DIM*DIM+j*DIM+k]/100);
        if (u<=0) u=0;
        if (u>=9) u=9;
        histogrammy[u]++;
      }
    }
  }
  return (double) (dot_product+moving_average+pi+pi2);


}
