	.SPACE $PRIVATE$
	.SUBSPA $DATA$,QUAD=1,ALIGN=8,ACCESS=31
	.SUBSPA $BSS$,QUAD=1,ALIGN=8,ACCESS=31,ZERO,SORT=82
	.SPACE $TEXT$
	.SUBSPA $LIT$,QUAD=0,ALIGN=8,ACCESS=44
	.SUBSPA $CODE$,QUAD=0,ALIGN=8,ACCESS=44,CODE_ONLY

	.level 2.0
	add %r2,%r20,%r31
	add,l %r2,%r20,%r31
	add,tsv %r2,%r20,%r31
	add,c %r2,%r20,%r31
	add,c,tsv %r2,%r20,%r31
	add,dc %r2,%r20,%r31
	add,dc,tsv %r2,%r20,%r31
	add,= %r2,%r20,%r31
	add,l,< %r2,%r20,%r31
	add,tsv,<= %r2,%r20,%r31
	add,c,nuv %r2,%r20,%r31
	add,c,tsv,znv %r2,%r20,%r31
	add,dc,sv %r2,%r20,%r31
	add,dc,tsv,od %r2,%r20,%r31
	add,tr %r2,%r20,%r31
	add,l,<> %r2,%r20,%r31
	add,tsv,>= %r2,%r20,%r31
	add,c,> %r2,%r20,%r31
	add,c,tsv,uv %r2,%r20,%r31
	add,dc,vnz %r2,%r20,%r31
	add,dc,tsv,nsv %r2,%r20,%r31
	add,dc,tsv,ev %r2,%r20,%r31
	add,* %r2,%r20,%r31
	add,*= %r2,%r20,%r31
	add,l,*< %r2,%r20,%r31
	add,tsv,*<= %r2,%r20,%r31
	add,c,*nuv %r2,%r20,%r31
	add,c,tsv,*znv %r2,%r20,%r31
	add,dc,*sv %r2,%r20,%r31
	add,dc,tsv,*od %r2,%r20,%r31
	add,*tr %r2,%r20,%r31
	add,l,*<> %r2,%r20,%r31
	add,tsv,*>= %r2,%r20,%r31
	add,c,*> %r2,%r20,%r31
	add,c,tsv,*uv %r2,%r20,%r31
	add,dc,*vnz %r2,%r20,%r31
	add,dc,tsv,*nsv %r2,%r20,%r31
	add,dc,tsv,*ev %r2,%r20,%r31
	addi 5,%r20,%r31
	addi,tsv 5,%r20,%r31
	addi,tc 5,%r20,%r31
	addi,tsv,tc 5,%r20,%r31
	addi,= 5,%r20,%r31
	addi,tsv,<= 5,%r20,%r31
	addi,tc,sv 5,%r20,%r31
	addi,tsv,tc,od 5,%r20,%r31
	addi,tr 5,%r20,%r31
	addi,tsv,>= 5,%r20,%r31
	addi,tc,vnz 5,%r20,%r31
	addi,tsv,tc,nsv 5,%r20,%r31
	addi,tsv,tc,ev 5,%r20,%r31