#ifndef __FREERTOS_UTILS_H
#define __FREERTOS_UTILS_H

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "stream_buffer.h"
#include "message_buffer.h"

#ifdef __cplusplus
extern "C" {
#endif

void FrtosGetTaskInfo(TaskHandle_t task);
void FrtosGetSytemTaskInfo(void);
void FrtosGetHeapInfo(void);

#ifdef __cplusplus
}
#endif

//  EventGroup  //  EventGroup  //  EventGroup  //  EventGroup  //  EventGroup  //

#define FRTOS_EventGroupCreateStatic(handle) \
do{ \
	static StaticEventGroup_t staticEventGroup; \
	(handle) = xEventGroupCreateStatic(&staticEventGroup); \
}while(0)

//  MessageBuffer  //  MessageBuffer  //  MessageBuffer  //  MessageBuffer  //

#define FRTOS_MessageBufferCreateStatic(bufferSize, handle) \
do{ \
	static uint8_t buffer [bufferSize]; \
	static StaticMessageBuffer_t staticStreamBuffer; \
	(handle) = xMessageBufferCreateStatic( \
		bufferSize, \
		buffer, \
		&staticStreamBuffer); \
}while(0)

//  Mutex  //  Mutex  //  Mutex  //  Mutex  //  Mutex  //  Mutex  //

#define FRTOS_MutexCreateStatic(handle) \
do{ \
	static StaticSemaphore_t staticMutex; \
	(handle) = xSemaphoreCreateMutexStatic(&staticMutex); \
}while(0)

#define FRTOS_MutexCreateRecursiveStatic(handle) \
do{ \
	static StaticSemaphore_t staticMutex; \
	(handle) = xSemaphoreCreateRecursiveMutexStatic(&staticMutex); \
}while(0)

//  Queue  //  Queue  //  Queue  //  Queue  //  Queue  //  Queue  //

#define FRTOS_QueueCreateStatic(queueSize, itemSize, handle) \
do{ \
	static uint8_t buffer [queueSize * itemSize]; \
	static StaticQueue_t staticQueue; \
	(handle) = xQueueCreateStatic( \
		queueSize, \
		itemSize, \
		buffer, \
		&staticQueue); \
}while(0)

//  Semaphore  //  Semaphore  //  Semaphore  //  Semaphore  //

#define FRTOS_SemaphoreCreateBinaryStatic(handle) \
do{ \
	static StaticSemaphore_t staticSemaphore; \
	(handle) = xSemaphoreCreateBinaryStatic(&staticSemaphore); \
}while(0)

#define FRTOS_SemaphoreCreateCountingStatic(maxCount, initialCount, handle) \
do{ \
	static StaticSemaphore_t staticSemaphore; \
	(handle) = xSemaphoreCreateCountingStatic( \
								 maxCount, \
								 initialCount, \
								 &staticSemaphore); \
}while(0)

//  StreamBuffer  //  StreamBuffer  //  StreamBuffer  //  StreamBuffer  //

#define FRTOS_StreamBufferCreateStatic(bufferSize, triggerLevel, handle) \
do{ \
	static uint8_t buffer [bufferSize]; \
	static StaticStreamBuffer_t staticStreamBuffer; \
	(handle) = xStreamBufferCreateStatic( \
		bufferSize, \
		triggerLevel, \
		buffer, \
		&staticStreamBuffer); \
}while(0)

//  Task  //  Task  //  Task  //  Task  //  Task  //  Task  //

/**@brief Allocate static memory and create task
 * @note: if task created from another task it must be in
 * vTaskSuspendAll/xTaskResumeAll section! Or task can possibly
 * start before handle became valid
 */
#define FRTOS_TaskCreateStatic(functionName, debugName, stackSize, param, prior, handle) \
do{ \
	static StackType_t stack [stackSize]; \
	static StaticTask_t staticTask; \
	(handle) = xTaskCreateStatic( \
		(functionName), \
		(debugName), \
		(stackSize), \
		(param), \
		(prior), \
		stack, \
		&staticTask); \
}while(0)

/**@brief Allocate static memory and create task under task suspend
 */
#define FRTOS_TaskCreateStaticSafe(functionName, debugName, stackSize, param, prior, handle) \
do{ \
	vTaskSuspendAll(); \
	static StackType_t stack [stackSize]; \
	static StaticTask_t staticTask; \
	(handle) = xTaskCreateStatic( \
		(functionName), \
		(debugName), \
		(stackSize), \
		(param), \
		(prior), \
		stack, \
		&staticTask); \
	if(!xTaskResumeAll()) taskYIELD(); \
}while(0)

/**@brief Wait for notification value bit only if it was cleared
 */
#define FRTOS_TaskNotifyWaitBit(DELAY) \
do{ \
	if(!ulTaskNotifyValueClear(NULL, 0)){ \
		xTaskNotifyWait(0, 0, NULL, DELAY); \
	} \
}while(0)

/**@brief Wait for notification value bit only if it was cleared
 * Indexed version
 */
#define FRTOS_TaskNotifyWaitBitIndexed(DELAY, INDEX) \
do{ \
	if(!ulTaskNotifyValueClearIndexed(NULL, INDEX, 0)){ \
		xTaskNotifyWaitIndexed(INDEX, 0, 0, NULL, DELAY); \
	} \
}while(0)

/**@brief Check bit state
 */
#define FRTOS_TaskNotifyCheckBit(BIT) \
	(ulTaskNotifyValueClear(NULL, 0) & (BIT))

/**@brief Check bit state.
 * Indexed version
 */
#define FRTOS_TaskNotifyCheckBitIndexed(BIT, INDEX) \
	(ulTaskNotifyValueClearIndexed(NULL, INDEX, 0) & (BIT))

/**@brief Clear notification value bit and check bit state
 */
#define FRTOS_TaskNotifyTakeBit(BIT) \
	(ulTaskNotifyValueClear(NULL, BIT) & (BIT))

/**@brief Clear notification value bit and check bit state
 * Indexed version
 */
#define FRTOS_TaskNotifyTakeBitIndexed(BIT, INDEX) \
	(ulTaskNotifyValueClearIndexed(NULL, INDEX, BIT) & (BIT))

//  Timers  //  Timers  //  Timers  //  Timers  //  Timers  //  Timers  //

#define FRTOS_TimerCreateStatic(debugName, period, isAutoreload, id, callback, handle) \
do{ \
	static StaticTimer_t staticTimer; \
	(handle) = xTimerCreateStatic((debugName), (period), (isAutoreload), (id), (callback), &staticTimer); \
}while(0)

#if configSUPPORT_STATIC_ALLOCATION
	/* static memory allocation for the IDLE task */
	#define IDLE_TASK_SIZE configMINIMAL_STACK_SIZE
	static StaticTask_t IdleTaskTCBBuffer;
	static StackType_t IdleStack[IDLE_TASK_SIZE];

	#if (configUSE_TIMERS == 1)
		static StaticTask_t TimerTaskTCBBuffer;
		static StackType_t TimerStack[configTIMER_TASK_STACK_DEPTH];
	#endif
#endif

enum FrtosPriorityE
{
	FRTOS_PRIORITY_0 = 0U,
	FRTOS_PRIORITY_1 = 1U,
	FRTOS_PRIORITY_2 = 2U,
	FRTOS_PRIORITY_3 = 3U,
	FRTOS_PRIORITY_4 = 4U,
	FRTOS_PRIORITY_5 = 5U,
	FRTOS_PRIORITY_6 = 6U,
	FRTOS_PRIORITY_7 = 7U,
	FRTOS_PRIORITY_8 = 8U,
	FRTOS_PRIORITY_9 = 9U
};

enum FrtosTimerTypeE
{
	FRTOS_TIMER_ONE_SHOT   = pdFALSE,
	FRTOS_TIMER_AUTORELOAD = pdTRUE
};

#endif	/*__FREERTOS_UTILS_H*/
