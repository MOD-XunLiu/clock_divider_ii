/*
Copyright DornerWorks 2016

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
following conditions are met:
1.	 Redistributions of source code must retain the above copyright notice, this list of conditions and the
following disclaimer.

THIS SOFTWARE IS PROVIDED BY DORNERWORKS FOR USE ON THE CONTRACTED PROJECT, AND ANY EXPRESS OR IMPLIED WARRANTY
IS LIMITED TO THIS USE. FOR ALL OTHER USES THIS SOFTWARE IS PROVIDED ''AS IS'' AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL DORNERWORKS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "xen.h"


.globl HYPERVISOR_console_io;
.align 4;
HYPERVISOR_console_io:
    mov x16, __HYPERVISOR_console_io;
    hvc 0xEA1;
    ret;


.globl HYPERVISOR_hvm_op;
.align 4;
HYPERVISOR_hvm_op:
    mov x16, __HYPERVISOR_hvm_op;
    hvc 0xEA1;
    ret;

.globl HYPERVISOR_memory_op;
.align 4;
HYPERVISOR_memory_op:
    mov x16, __HYPERVISOR_memory_op;
    hvc 0xEA1;
    ret;

.globl HYPERVISOR_event_channel_op;
.align 4;
HYPERVISOR_event_channel_op:
    mov x16, __HYPERVISOR_event_channel_op
    hvc 0xEA1;
    ret;
