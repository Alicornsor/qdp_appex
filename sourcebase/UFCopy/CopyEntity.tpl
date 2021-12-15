!!travel self!!
#ifndef Copy!!@name!!Entity
#define Copy!!@name!!Entity(target,source)	\
	!!travel self!!
		!!if !strcmp(@name,"Ref")!!
			Copy!!@entity!!Entity(target,source);	\
		!!else!!
			(target)->!!@name!!=(source)->!!@name!!;	\
		!!endif!!
	!!next!!

#endif
!!next!!
