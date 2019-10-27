TOP 	  = VGA_bitmap
#Liste des TOP autorisés
TOP_OK	  = VGA_bitmap Compteur lecture_memoire
#ifeq ($(TOP), VGA_bitmap)
  MEM_FILE :=img.mem
  DATA_VHD :=vhd/prog_data.vhd
#endif

FPGA	  = xc7z010-clg400-1
SIMU_EXE  = $(TB_ENTITY)_isim_beh.exe

SIMU_WBD  = $(subst .exe,.wbd,$(SIMU_EXE))
VHDDIR    = vhd

TOCLEAN   = $(filter %log %.html %.xml %.bgn %.bld %.drc %.lso %.ncd %.pad\
			%.par %.pcf %.ptwx %.syr %.unroutes %.xpi %.ngc %.ngd %.exe\
			%.xwbt %.map %.xrpt %.ngm %.mrp %.ngr %.csv %.txt %.twr %.twx\
			$(addsuffix .prj,$(TOP_OK)) %.sym %.wdb %.ini fuse%,$(wildcard *))

TOPOLISH  = $(TOCLEAN) iseconfig isim xst download.bit xlnx_auto_0_xdb\
			$(wildcard $(SRCDIR)/*.mem*) $(wildcard _*)

XST_FILE := config.xst
UT_FILE	 := config.ut

VERB	 := 1
q 		  = $(if $(filter 1, $(VERB)),$1,\
				$(if $(2),@echo $2 && $1 > $3 2>&1, @$1))
ifdef MEM_FILE
	TARGET:=golden.bit
	BMM_FILE:=$(TOP).bmm
	BMMBD_FILE:=$(TOP)_bd.bmm
	BMM_OPT:= -bm $(BMM_FILE)
else
	TARGET:=download.bit
endif

# Verification que l'environement de Xilinx a bien été sourcé
ifeq ($(origin XILINX), undefined)
  $(error Outils Xilinx introuvables, lancez d'abord la commande "source /Xilinx/env-14.7.sh") #'
endif

# Verification que le TOP est autorisé
ifeq ($(filter $(TOP),$(TOP_OK)),)
  $(error Toplevel $(TOP) inconnu)
endif

# Les Toplevels du TP
  TOP_REEL	:= $(TOP)
  PROG_PRJ      := $(TOP).prj
  TB_ENTITY	:= tb_$(TOP)
  SIMU_PRJ  	:= tb_$(TOP).prj
# Simulation
  SIMU_TIME 	:= 20 ns
  SIMU_ADD  	:= /

# Programmation OK par défaut
  ENABLE_PROG 	:= 1
  ENABLE_BACKEND:= 1
  VERBOSE :=-intstyle xflow # mettre xflow ou silent
ifdef  OPT
	OPT_EFFORT := -ol high -xe n
	MAP_OPT :=-register_duplication on -logic_opt on
else
	OPT_EFFORT := -ol std
endif


# Ajustement au cas par cas
ifeq ($(TOP), VGA_mire)
  TB_ENTITY	:= tb_VGA
  TOP_REEL	:= VGA
endif
ifeq ($(TOP), RAM)
  ENABLE_PROG 	:= 0
  SIMU_TIME 	:= 120 ns
endif
ifeq ($(TOP), VGA_bitmap)
  TB_ENTITY	:= tb_VGA
  TOP_REEL	:= VGA
endif

ifdef IMG
$(MEM_FILE): force
	convert $(IMG) -resize 640x480 -extent 640x480 -depth 2 -colorspace RGB -compress none ppm:- | awk 'BEGIN {v=0;n0=12;n=n0; printf "@0 "} NR>3 {for (i=1;i<=NF;i++) {n--; v+=lshift(rshift($$i,6),2*n) ; if (n==0) { printf "%06x\n", v;v=0;n=n0} }} ' > $@
	#$(call q, $(AS) $<, "  AS     $<",as.log)
force:
endif

UCF_FILE  	:= $(TOP_REEL).ucf
VHD_SRC		:= $(shell sed -e 's/vhdl work "\(.*\)"/\1 /' $(SIMU_PRJ))

all: $(SIMU_EXE)

.PHONY: compil clean realclean

$(SIMU_EXE): compil

$(DATA_VHD): $(MEM_FILE)
	$(call q,\
	   	data2mem $(BMM_OPT) -bd $< -o h $@ && \
		sed -i s/_tpoot24//g $@ , "  MAJ du code    ",$@.log)

compil: $(VHD_SRC)
	$(call q,\
	   	fuse $(VERBOSE) -incremental -lib secureip\
		-o $(SIMU_EXE) -prj $(SIMU_PRJ) \
	       	work.$(TB_ENTITY) , "  Compilation    ",$@.log)

# Génération du fichier de synthèse
$(PROG_PRJ): $(SIMU_PRJ)
	@grep -i -v -- "$(TB_ENTITY)" $< >$@

run_simu: $(SIMU_EXE)
	@sed -i 's/run .*/run $(SIMU_TIME);/g' isim.cmd
ifndef MAGIC_VIEW
	@sed -i 's+wave .*+wave add $(SIMU_ADD) +g' isim.cmd
endif
	$(call q, ./$< -gui -tclbatch isim.cmd -wdb\
	       $(SIMU_WBD) $(MAGIC_VIEW), "  Simulation   ",simu.log)

synthese: $(TOP).ngc

$(TOP).ngc:  $(filter-out $(DATA_VHD) %$(TB_ENTITY).vhd,$(VHD_SRC)) $(PROG_PRJ) | $(DATA_VHD)
	@sed -i 's/^-ifn .*/-ifn $(PROG_PRJ)/' $(XST_FILE)
	@sed -i 's/^-ofn .*/-ofn $(TOP)/' $(XST_FILE)
	@sed -i 's/^-top .*/-top $(TOP_REEL)/' $(XST_FILE)
	$(call q, mkdir -p xst/projnav.tmp/ && \
		xst $(VERBOSE) -ifn\
	       	$(XST_FILE) -ofn $(TOP).syr , "  Synthèse logique",synthese.log)

ifeq ($(ENABLE_BACKEND), 1)
$(TOP).ngd: $(TOP).ngc $(UCF_FILE)
	$(call q, ngdbuild $(VERBOSE) $(BMM_OPT)\
       	-dd _ngo -nt timestamp -uc $(UCF_FILE) -p $(FPGA) $< $@  \
		, "  Projection technologique sur le FPGA choisi (choix des blocs de base)", map.log)
$(TOP).pcf: $(TOP).ngd
	$(call q,	map $(VERBOSE) -p $(FPGA) -w $(OPT_EFFORT) $(MAP_OPT) -r 4 \
		-o $*_map.ncd $< $@ , "  Placement (des blocs de base dans le FPGA)",place.log)
$(TOP).ncd: $(TOP).pcf
	$(call q, par -w $(VERBOSE) $(OPT_EFFORT) $*_map.ncd $@ $< \
		, "  Routage (interconnection des blocs de base)",route.log)

$(TARGET): $(TOP).ncd
	$(call q, bitgen $(VERBOSE) -f $(UT_FILE) $< $@ \
		, "  Génération du fichier de configuration",gene.log)

$(BMMBD_FILE): $(TOP).ncd
	$(call q, bitgen -j -d -w -bd $(MEM_FILE) $<,)
endif

ifeq ($(ENABLE_PROG), 1)
ifdef MEM_FILE
download.bit:$(TARGET) $(MEM_FILE) $(BMMBD_FILE)
	$(call q, data2mem -bd $(MEM_FILE) -bm $(BMMBD_FILE) -bt $< -o b $@, "  MAJ du fichier de configuration")
endif

run_fpga: download.bit impact.cmd
	$(call q, impact -batch impact.cmd, "  Programmation",prog.log)
else

run_fpga:
	$(error Programmation non prévue pour le toplevel $(TOP))

endif

clean:
	$(call q,rm -f $(TOCLEAN),)

realclean: clean
	$(call q, rm -rf $(TOPOLISH),)
