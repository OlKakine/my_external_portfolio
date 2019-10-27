.text
.globl set_alarm
set_alarm:
	/* A completer */
	mtc0 $0, $9 /* mtc0 move values from general register to coprocessor register */
	/* inversement pr mfc0*/
	mtc0 $a0, $11
    jr $ra


/* void  pushbtn_irq_hdl(void)*/
/* A compléter */


.sdata
/* struct compt *param; */
.globl param
param: .long 0x0
