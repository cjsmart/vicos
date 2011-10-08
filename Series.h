/* 
 * File:   Series.h
 * Author: cjsmart <alexey.pozin@gmail.com>
 *
 * Created on 15 Август 2011 г., 15:12
 */

#ifndef SERIES_H
#define	SERIES_H

#include "Includes.h"

namespace vicos
{

typedef double numeric;
typedef double time;
typedef vector<numeric> timepoint;
typedef vector<timepoint> series;
typedef vector<series> seriesmatrix;

};

#endif	/* SERIES_H */

