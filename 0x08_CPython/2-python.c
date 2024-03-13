#include <python3.4/Python.h>
#include <python3.4/listobject.h>
#include <python3.4/object.h>
#include <python3.4/bytesobject.h>

/**
* print_python_bytes - prints some basic info about Python bytes
* @p: Python Object
*
* Return: void
*/
void print_python_bytes(PyObject *p)
{
	PyBytesObject *pb = (PyBytesObject *)p;

	printf("[.] bytes object info\n");
	if (PyBytes_Check(p))
	{
		printf("  size: %ld\n", pb->ob_base.ob_size);
		printf("  trying string: %s\n", pb->ob_sval);
		if (pb->ob_base.ob_size < 10)
			printf("  first %ld bytes: %s\n", pb->ob_base.ob_size + 1, pb->ob_sval);
		else
		{
			for (Py_ssize_t i = 0; i < pb->ob_base.ob_size && i < 10; ++i)
			{
				printf("%02hhx ", pb->ob_sval[i]);
			}
			printf("\n");
		}
	}
	else
	{
		printf("  [ERROR] Invalid Bytes Object\n");
	}
}
