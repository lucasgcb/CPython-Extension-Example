// Always define this before including Python Header.
#define PY_SSIZE_T_CLEAN // Make the handler "s#" use Py_ssize_t rather than int.

/* implements pre-processors definitions which are critical.
   Needs to be included before any standard headers! */
#include <Python.h>  
#define MODULE_NAME "mymath"
#define _MODULE_DEF PyInit_mymath
/* <Python.h> already includes:
      - <stdlib.h>
      - <stdio.h>
      - <string.h>
      - <errno.h> */

PyMODINIT_FUNC // definition in header for initializing the module      
_MODULE_DEF(void);
static PyObject* add(PyObject*, PyObject*);

int main(int argc, char *argv[])
{
    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }

    /* Add a built-in module, before Py_Initialize */
    PyImport_AppendInittab(MODULE_NAME, _MODULE_DEF);

    /* Pass argv[0] to the Python interpreter */
    Py_SetProgramName(program);

    /* Initialize the Python interpreter.  Required. */
    Py_Initialize();

    /* Optionally import the module; alternatively,
       import can be deferred until the embedded script
       imports it. */
    PyImport_ImportModule(MODULE_NAME);


    PyMem_RawFree(program); // free memory
    return 0;
}

static PyObject* add(PyObject *self, PyObject *args)
{
    /*
     * Take two numbers and return their sum.
     */

    Py_ssize_t TupleSize = PyTuple_Size(args);
    int number1; /* Store Our Custom Command here */
    int number2; /* Store Our Custom Command here */
    int sts;             /* Return value */
    /* 
     * Python objects need to be parsed to C values. 
     */
    if (!PyArg_ParseTuple(args, "ii", &number1, &number2)) // The chars in the string define the conversion type.
                                                           // Full list: https://docs.python.org/3/c-api/arg.html#strings-and-buffers
        return NULL;  /* Standard error return value
                         Errors can also return Python Objects */

    sts = number1 + number2;
    return PyLong_FromLong(sts); // Turn C return value into Python integer object
    // Macro for None Value: Py_None
}


/* The following is the method table. It defines
   what methods are available within our module. */

static PyMethodDef methods[] = {
    {"add",  // name of the method!
    add, // Pointer to the C function for this method
    METH_VARARGS, // Describes convention: This C Function accepts a PyObject* whih is a dict of keywords.
    "This is the docstring for the adder method."},
    {NULL, NULL, 0, NULL}        /* Sentinel for dark magic */
};


/* The following is the module definition. 
   It stores the name of the module, the module docstring 
   and the Method table. */

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT, // This macro is explicitly demanded by the Documentation gods
    MODULE_NAME,   /* name of module */
    "This is the mymath's documentation string.", /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    methods
};

PyMODINIT_FUNC // definition in header for initializing the module
_MODULE_DEF(void) // This function name also defines the module name!
{
    return PyModule_Create(&module); // Return NULL if something goes wrong.
}
