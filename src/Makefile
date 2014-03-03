#
# OMNeT++/OMNEST Makefile for CS381_Torrent_HW2
#
# This file was generated with the command:
#  opp_makemake -f --deep -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/linklayer/ethernet -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/linklayer/ieee80211/radio -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/networklayer/common -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/networklayer/icmpv6 -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/world/obstacles -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/mobility -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/networklayer/contract -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/networklayer/manetrouting/base -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/networklayer/xmipv6 -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/networklayer/autorouting/ipv4 -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/linklayer/ieee80211/mgmt -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/util -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/linklayer/common -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/transport/contract -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/status -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/linklayer/radio/propagation -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/linklayer/ieee80211/radio/errormodel -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/linklayer/radio -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/util/headerserializers/tcp -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/networklayer/ipv4 -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/util/headerserializers/ipv4 -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/base -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/util/headerserializers -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/world/radio -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/linklayer/ieee80211/mac -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/networklayer/ipv6 -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/transport/sctp -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/util/headerserializers/udp -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/networklayer/ipv6tunneling -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/battery/models -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/applications/pingapp -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/linklayer/contract -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/util/headerserializers/sctp -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/transport/tcp_common -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/networklayer/arp -I/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/src/transport/udp -L/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet/out/$(CONFIGNAME)/src -linet -DINET_IMPORT -KINET_PROJ=/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet
#

# Name of target to be created (-o option)
TARGET = CS381_Torrent_HW2$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I$(INET_PROJ)/src/linklayer/ethernet \
    -I$(INET_PROJ)/src/linklayer/ieee80211/radio \
    -I$(INET_PROJ)/src/networklayer/common \
    -I$(INET_PROJ)/src \
    -I$(INET_PROJ)/src/networklayer/icmpv6 \
    -I$(INET_PROJ)/src/world/obstacles \
    -I$(INET_PROJ)/src/mobility \
    -I$(INET_PROJ)/src/networklayer/contract \
    -I$(INET_PROJ)/src/networklayer/manetrouting/base \
    -I$(INET_PROJ)/src/networklayer/xmipv6 \
    -I$(INET_PROJ)/src/networklayer/autorouting/ipv4 \
    -I$(INET_PROJ)/src/linklayer/ieee80211/mgmt \
    -I$(INET_PROJ)/src/util \
    -I$(INET_PROJ)/src/linklayer/common \
    -I$(INET_PROJ)/src/transport/contract \
    -I$(INET_PROJ)/src/status \
    -I$(INET_PROJ)/src/linklayer/radio/propagation \
    -I$(INET_PROJ)/src/linklayer/ieee80211/radio/errormodel \
    -I$(INET_PROJ)/src/linklayer/radio \
    -I$(INET_PROJ)/src/util/headerserializers/tcp \
    -I$(INET_PROJ)/src/networklayer/ipv4 \
    -I$(INET_PROJ)/src/util/headerserializers/ipv4 \
    -I$(INET_PROJ)/src/base \
    -I$(INET_PROJ)/src/util/headerserializers \
    -I$(INET_PROJ)/src/world/radio \
    -I$(INET_PROJ)/src/linklayer/ieee80211/mac \
    -I$(INET_PROJ)/src/networklayer/ipv6 \
    -I$(INET_PROJ)/src/transport/sctp \
    -I$(INET_PROJ)/src/util/headerserializers/udp \
    -I$(INET_PROJ)/src/networklayer/ipv6tunneling \
    -I$(INET_PROJ)/src/battery/models \
    -I$(INET_PROJ)/src/applications/pingapp \
    -I$(INET_PROJ)/src/linklayer/contract \
    -I$(INET_PROJ)/src/util/headerserializers/sctp \
    -I$(INET_PROJ)/src/transport/tcp_common \
    -I$(INET_PROJ)/src/networklayer/arp \
    -I$(INET_PROJ)/src/transport/udp \
    -I.

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L$(INET_PROJ)/out/$(CONFIGNAME)/src  -linet
LIBS += -Wl,-rpath,`abspath $(INET_PROJ)/out/$(CONFIGNAME)/src`

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = $O/Peer.o $O/Tracker.o $O/PeerToPeerMSG_m.o $O/PeerToTrackerMsg_m.o

# Message files
MSGFILES = \
    PeerToPeerMSG.msg \
    PeerToTrackerMsg.msg

# Other makefile variables (-K)
INET_PROJ=/Users/violettavylegzhanina/omnetpp-4.3.1/samples/inet

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS) -DINET_IMPORT $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f CS381_Torrent_HW2 CS381_Torrent_HW2.exe libCS381_Torrent_HW2.so libCS381_Torrent_HW2.a libCS381_Torrent_HW2.dll libCS381_Torrent_HW2.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/Peer.o: Peer.cc \
	Peer.h \
	PeerToPeerMSG_m.h \
	PeerToTrackerMsg_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	$(INET_PROJ)/src/transport/contract/TCPSocketMap.h
$O/PeerToPeerMSG_m.o: PeerToPeerMSG_m.cc \
	PeerToPeerMSG_m.h
$O/PeerToTrackerMsg_m.o: PeerToTrackerMsg_m.cc \
	PeerToTrackerMsg_m.h
$O/Tracker.o: Tracker.cc \
	PeerToPeerMSG_m.h \
	PeerToTrackerMsg_m.h \
	Tracker.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	$(INET_PROJ)/src/transport/contract/TCPSocketMap.h

