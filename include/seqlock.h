#ifndef PTHREAD_H
#include <pthread.h>

int read_num = 0;
int writer_numb = 0;
int sequence_num = 0;

typedef struct pthread_seqlock 
{ 
   pthread_mutex_t lock;
   //mutex lock for checking condition.
   pthread_cond_t  read;
   pthread_cond_t  writer;
        
   
} 

pthread_seqlock_t;

static inline void pthread_seqlock_init(pthread_seqlock_t *seqlock)
{
        pthread_mutex_init(&(seqlock->lock),NULL);
        pthread_cond_init(&(seqlock->read),NULL);
        pthread_cond_init(&(seqlock->writer),NULL);
        
}

static inline void pthread_seqlock_destroy(pthread_seqlock_t *seqlock){
        pthread_mutex_destroy(&(seqlock->lock));
        pthread_cond_destroy(&(seqlock->read));
        pthread_cond_destroy(&(seqlock->writer));
        
}

static inline unsigned pthread_seqlock_rdlock(pthread_seqlock_t *seqlock){
        pthread_mutex_lock(&(seqlock->lock));
        while(sequence_num % 2 == 1)
             pthread_cond_wait(&(seqlock->read), &(seqlock->lock));
        //if passing while, it mean that reader can enter now, so we return 1        
        read_num++;        
        pthread_mutex_unlock(&(seqlock->lock));
        return 1;
}

static inline unsigned pthread_seqlock_rdunlock(pthread_seqlock_t *seqlock){
        pthread_mutex_lock(&(seqlock->lock));
        read_num--;
        if(read_num == 0 && sequence_num % 2 == 0)
            pthread_cond_signal(&(seqlock->writer));
        pthread_mutex_unlock(&(seqlock->lock));
        return sequence_num % 2 == 0;
}

static inline void pthread_seqlock_wrlock(pthread_seqlock_t *seqlock){
        pthread_mutex_lock(&(seqlock->lock));
        writer_numb++;
        while(read_num > 0 || sequence_num % 2 == 1)
             pthread_cond_wait(&(seqlock->writer), &(seqlock->lock));
        writer_numb--;
        sequence_num++;
        pthread_mutex_unlock(&(seqlock->lock));
        
}

static inline void pthread_seqlock_wrunlock(pthread_seqlock_t *seqlock){
        pthread_mutex_lock(&(seqlock->lock));
        sequence_num--;
        if(writer_numb > 0)
            pthread_cond_signal(&(seqlock->writer));
        
        pthread_cond_broadcast(&(seqlock->read));
        pthread_mutex_unlock(&(seqlock->lock));
        
}
#endif
