/*
 * GPIO_def.h
 *
 * Created: 06.02.2017 01:38:00
 *  Author: Peter Buchegger
 */

#ifndef GPIO_DEF_H_
#define GPIO_DEF_H_

// M1_DIR: 42 - PL7
#define M1_DIR			&gpio[ePORTL][7]

// M1_STEP: 40 - PG1
#define M1_STEP			&gpio[ePORTG][1]

// M1_ENABLE: 44 - PL5
#define M1_ENABLE		&gpio[ePORTL][5]


// M2_DIR: 20 - PD1
#define M2_DIR			&gpio[ePORTD][1]

// M2_STEP: 21 - PD0
#define M2_STEP			&gpio[ePORTD][0]

// M2_ENABLE: 38 - PD7
#define M2_ENABLE		&gpio[ePORTD][7]

#endif /* GPIO_DEF_H_ */
