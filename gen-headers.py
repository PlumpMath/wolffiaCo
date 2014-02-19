#! /usr/bin/python

task_test_tmpl = """
#ifdef WO_TASK{0}
#define __woRunTask{0} __woRunTask(WO_TASK{0})
#else
#define __woRunTask{0}
#endif
"""

def gen_tasks(size):
    out = file('include/wolffia-task-gen.h', 'wt')

    for i in range(size):
        print >>out, task_test_tmpl.format(i)

    print >>out, "#define WO_RunOS() while(true) {\\"

    for i in range(size):
        print >>out, "\t__woRunTask{0}\\".format(i)

    print >>out, "}"
    
    out.close()

gen_tasks(32)