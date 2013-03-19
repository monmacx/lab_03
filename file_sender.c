#include "file_sender.h"

void *send_file_to_client(void *ptr)
{
	struct _message *mes;
	mes = (struct message *)ptr;
  printf("%d\n %s\n %d\n", mes->index, mes->file, mes->size);
	write(mes->index, mes->file, mes->size);
	return;
}