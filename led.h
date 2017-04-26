#ifndef LED_H
#define LED_H

typedef struct {
	void * (*ledOn)(void *);
}t_method_led;

#endif
