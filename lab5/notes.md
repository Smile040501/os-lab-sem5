# POSIX Thread (pthread) libraries

## Basics

### API

```cpp
#include <pthread.h>

// Creates a thread id
pthread_t tid;

// Create attributes
pthread_attr_t attr;
// Initializing attribute
int pthread_attr_init(pthread_attr_t *attr);

/**
 * Creates a new thread i.e. sets the function passed to keep executing in the background
 * @returns: 0 if thread creation was successful
 *
 * Set `attr` to NULL if default thread attributes are to be used.
 *
 * The argument `void*` is sent as an argument to the function
*/
int pthread_create(pthread_t * thr,
                       const pthread_attr_t * attr,
                       void * (*func)(void *),
                       void *arg);

/**
 * Wait for termination of this thread
 * We can pass a pointer an capture the return value of the thread passed in `pthread_exit`
 */
int pthread_join(pthread_t th, void **res);

/**
 * Terminates the calling thread, equivalent to returning from the thread function
 */
void pthread_exit(void *retval);

// Creating a default mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Acquire a lock on the specific mutex variable. If the mutex is already locked by another thread, this call will block the calling thread until the mutex is unlocked.
int pthread_mutex_lock(pthread_mutex_t *m);

// Unlock a mutex variable. An error is returned if mutex is already unlocked or owned by another thread.
int pthread_mutex_unlock(pthread_mutex_t *m);

// Attempt to lock a mutex or will return error code if busy. Useful for preventing deadlock conditions.
int pthread_mutex_trylock(pthread_mutex_t *m);
```

### Examples

**Single Thread**

```cpp
#include <pthread.h>

#include <iostream>
int ans = 0;

void *sum(void *arg) {
    int *limit_arg = (int *)arg;
    int limit = *limit_arg;

    for (int i = 0; i <= limit; ++i) {
        ans += i;
    }

    pthread_exit(nullptr);
}

int main() {
    int limit = 5;
    pthread_t tid;

    pthread_create(&tid, nullptr, sum, &limit);

    // We can do other stuff here...
    // Thread will keep running in the background

    pthread_join(tid, nullptr);

    std::cout << ans << std::endl;

    return EXIT_SUCCESS;
}
```

**Instead of having one common global variable for all threads using same function, we can instead also pass a pointer to a structure and make an `answer` field in structure that will carry the final answer**

**Never return statically allocated pointers through `pthread_exit` as they will give error, instead dynamically allocate pointer and then pass it**

**Never pass a pointer that is within local scope (let say `for` loop) as last argument to `pthread_create` as in next iteration of `for` loop that pointer will not exits. So instead create an array of pointer objects outside the current scope**

```cpp
void *sum(void *arg) {
    // ... code here ...

    // Having local variable, instead of global
    int ans = 0;

    // Pass back data in dynamically allocated memory
	int *answer = new int;
	*answer = ans;
	pthread_exit(answer);
}

int main() {
    // ... code here ...

    // Wait until thread is done its work
	int *result;
	pthread_join(tid, (void**)&result);
    std::cout << "Sum is: " << (*result);
    delete result;

    return EXIT_SUCCESS;
}
```

**Mutex Synchronization**

```cpp
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int ans = 0;

void *sum(void *arg) {
    // ... code here ...

    for (int i = 0; i <= limit; ++i) {
        // Start of critical section
        pthread_mutex_lock(&mutex);

        // Contains variables section that include variables that are also used by other threads
        ans += i;

        // End Critical Section
        pthread_mutex_unlock(&mutex);
    }
}
```
