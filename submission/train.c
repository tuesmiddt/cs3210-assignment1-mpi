#include "train.h"

#define TRAIN_NUM_FIELDS 3
#define TRAIN_ID 0
#define TRAIN_LINE_ID 1
#define TRAIN_TRAVELLING_FORWARD 2

void train_init(train_t* train, int id, int line_id, bool travelling_forward)
{
    train->id = id;
    train->line_id = line_id;
    train->travelling_forward = travelling_forward;
}

void train_send(train_t* train, int dest, MPI_Comm comm)
{
    int data[TRAIN_NUM_FIELDS];
    int tag = TRAIN_NO_TRAIN;

    if (train != NULL) {
        tag = TRAIN_GOT_TRAIN;
        data[TRAIN_ID] = train->id;
        data[TRAIN_LINE_ID] = train->line_id;
        data[TRAIN_TRAVELLING_FORWARD] = train->travelling_forward;
    }
    MPI_Send(data, TRAIN_NUM_FIELDS, MPI_INT, dest, tag, comm);
}

int train_recv(train_t* train, int source, MPI_Comm comm)
{
    int data[TRAIN_NUM_FIELDS];
    MPI_Status status;
    MPI_Recv(data, TRAIN_NUM_FIELDS, MPI_INT, source, MPI_ANY_TAG, comm, &status);
    train->id = data[TRAIN_ID];
    train->line_id = data[TRAIN_LINE_ID];
    train->travelling_forward = data[TRAIN_TRAVELLING_FORWARD];
    return status.MPI_TAG;
}
