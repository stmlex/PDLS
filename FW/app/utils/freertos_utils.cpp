#include "freertos_utils.h"

#include "log_libs.h"
#define LOG_MODULE_LEVEL 3

#if configSUPPORT_STATIC_ALLOCATION
extern "C" void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
	*ppxIdleTaskTCBBuffer = &IdleTaskTCBBuffer;
	*ppxIdleTaskStackBuffer = IdleStack;
	*pulIdleTaskStackSize = IDLE_TASK_SIZE;
}
	#if (configUSE_TIMERS == 1)
	extern "C" void vApplicationGetTimerTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
	{
		*ppxIdleTaskTCBBuffer = &TimerTaskTCBBuffer;
		*ppxIdleTaskStackBuffer = TimerStack;
		*pulIdleTaskStackSize = configTIMER_TASK_STACK_DEPTH;
	}
	#endif
#endif

void FrtosGetTaskInfo(TaskHandle_t task)
{
	#if configUSE_TRACE_FACILITY==1
	if(!task) return;
	TaskStatus_t status;
	eTaskState state = eInvalid;
	vTaskGetInfo(task, &status, true, state);
	LOG_INFO("%s #%d, stack: %d, prio: %d",
		status.pcTaskName,
		status.xTaskNumber,
		status.usStackHighWaterMark,
		status.uxCurrentPriority
	);
	#endif
}

void FrtosGetHeapInfo(void)
{
	#if(configSUPPORT_DYNAMIC_ALLOCATION==1)&&defined(tskKERNEL_VERSION_MAJOR)&&defined(tskKERNEL_VERSION_MINOR)
	#if(tskKERNEL_VERSION_MAJOR>=10)&&(tskKERNEL_VERSION_MINOR>=3)
	HeapStats_t status;
	vPortGetHeapStats(&status);
	// LOG_INFO("cur:%u min:%u large:%u small:%u",
	// 	status.xAvailableHeapSpaceInBytes,
	// 	status.xMinimumEverFreeBytesRemaining,
	// 	status.xSizeOfLargestFreeBlockInBytes,
	// 	status.xSizeOfSmallestFreeBlockInBytes
	// );
	// LOG_INFO("blocks:%u malloc:%u free:%u",
	// 	status.xNumberOfFreeBlocks,
	// 	status.xNumberOfSuccessfulAllocations,
	// 	status.xNumberOfSuccessfulFrees
	// );
	#endif
	#endif
}

void FrtosGetSytemTaskInfo(void)
{
	FrtosGetTaskInfo(xTaskGetIdleTaskHandle());
	#if (configUSE_TIMERS == 1)
		FrtosGetTaskInfo(xTimerGetTimerDaemonTaskHandle());
	#endif
}

#if (configSUPPORT_DYNAMIC_ALLOCATION==1 && defined(ALX_FREERTOS_MALLOC))
extern "C" void* malloc(size_t size)
{
	return pvPortMalloc(size);
}

extern "C" void free(void* ptr)
{
	vPortFree(ptr);
}
#endif
