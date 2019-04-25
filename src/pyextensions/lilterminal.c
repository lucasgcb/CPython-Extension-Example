// Always define this before including Python Header.
#define PY_SSIZE_T_CLEAN // Make the handler "s#" use Py_ssize_t rather than int.

/* implements pre-processors definitions which are critical.
   Needs to be included before any standard headers! */
#include <Python.h>  
/* <Python.h> already includes:
      - <stdlib.h>
      - <stdio.h>
      - <string.h>
      - <errno.h> */

#define MODULE_NAME "lilterminal" // This defines the module name.
#define _MODULE_DEF PyInit_lilterminal // This sets the module definition.


PyMODINIT_FUNC // definition in header for initializing the module      
_MODULE_DEF(void);
static PyObject* terminal_caller(PyObject*, PyObject*);
static PyObject* xablau_spewer(PyObject *self, PyObject *args);

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

static PyObject* terminal_caller(PyObject *self, PyObject *args)
{
    /*
     * This function interfaces python code with C's system() function.
     * Users will simply call the method and input the command on their interface.
     * /
    /* *self always points to the module object or object instance in memory
     * *args points to a tuple containing the Python arguments, which are Python objects 
     */

    const char *command; /* Store Our Custom Command here */
    int sts;             /* Return value */

    /* 
     * Python objects need to be parsed to C values. 
     */
    if (!PyArg_ParseTuple(args, "s", &command)) // Get arg, turn to string, store in command
                                                // The chars in the string pointer define the conversion type.
                                                // Full list: https://docs.python.org/3/c-api/arg.html#strings-and-buffers
        return NULL;  /* Standard error return value
                         Errors can also return Python Objects */
    sts = system(command);
    return PyLong_FromLong(sts); // Turn C return value into Python integer object
    // Macro for None Value: Py_None
}

static PyObject* xablau_spewer(PyObject *self, PyObject *args)
{
    /*
     * This function calls a hard-coded echo through C's system().
     */
    const char *command = "echo xablau"; 
    int sts;             /* Return value */
    sts = system(command); //The actual command
    return PyLong_FromLong(sts); // Turn C return value into Python integer object
    // Macro for None Value: Py_None
}


/* The following is the method table. It defines
   what methods are available within our module. */

static PyMethodDef TerminalMethods[] = {
    //********* FIRST METHOD ************//
    {"system",  // name of the method!
    terminal_caller, // Pointer to the C function for this method
    METH_VARARGS, // Describes convention: This C Function accepts a PyObject* whih is a dict of keywords.
     "This is the docstring for the system method."},
    //********* SECOND METHOD ************//
    {"xablau",  // name of the other method!
    xablau_spewer, // Pointer to the C function for this method
    METH_VARARGS, // Describes convention: This C Function accepts a PyObject* whih is a dict of keywords.
     "Spew a powerful spell"},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};


/* The following is the module definition. 
   It stores the name of the module, the module docstring 
   and the Method table. */

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT, // This macro is explicitly demanded by the Documentation gods
    MODULE_NAME,   /* name of module */
    "This is the lilterminal's documentation string.", /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    TerminalMethods
};

PyMODINIT_FUNC // definition in header for initializing the module
_MODULE_DEF(void) // This function name also defines the module name!
{
    return PyModule_Create(&module); // Return NULL if something goes wrong.
}
