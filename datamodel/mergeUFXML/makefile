.SUFFIXES:  .c .cpp .o .obj .a .lib

CPP=cl
LINK=link
LIB32=lib 
PREP=cl -nologo -EP
PUMP=pump
COPY=copy /y
DEL=del
MAKE=nmake
ECHO=echo

.cpp.obj:
	$(CPP) $(CPPFLAGS) $(INCLUDEDIR) -c $< >> output
	move $(@F) $(@D)

ISLIB=N
DEFINES=-DWINDOWS -DMSVC
target=mergeUFXML.exe

DEBUG_DEFINE=-DDEBUG -DDEBUG_LOG

APPEND_CPPFLAGS=-nologo -EHsc -MTd -Od -Gm -ZI -FD -Zm200

PROFILE_CPPFLAGS=

WARNING_CPPFLAGS=-W3

CPPFLAGS=              $(APPEND_CPPFLAGS) $(PROFILE_CPPFLAGS) $(WARNING_CPPFLAGS) $(DEBUG_DEFINE) $(DEFINES)

LIBS= kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib             

DEBUG_LDFLAGS=/DEBUG

MAP_LDFLAGS=

PROFILE_LDFLAGS=

WARNING_LDFLAGS=/WARN:2

LDFLAGS=             -nologo /FIXED:NO $(MAP_LDFLAGS) $(DEBUG_LDFLAGS) $(PROFILE_LDFLAGS) $(WARNING_LDFLAGS)

LIBARFLAGS=             -nologo $(MAP_LDFLAGS) $(DEBUG_LDFLAGS) $(PROFILE_LDFLAGS)

DLLARFLAGS=             -nologo /dll $(MAP_LDFLAGS) $(DEBUG_LDFLAGS) $(PROFILE_LDFLAGS)


all: code

code: clearoutput $(target)

clearoutput:
	@$(ECHO) Compiling... > output

platform_obj= ..\..\sourcebase\platform\system.obj  ..\..\sourcebase\platform\platform.obj  ..\..\sourcebase\platform\mpath.obj 
platform_include= ..\..\sourcebase\platform\system.h  ..\..\sourcebase\platform\platform.h  ..\..\sourcebase\platform\mpath.h 
platform_includedir=-I..\..\sourcebase\platform\.
base_obj= ..\..\sourcebase\base\CBaseObject.obj  ..\..\sourcebase\base\BaseFunction.obj  ..\..\sourcebase\base\DesignError.obj  ..\..\sourcebase\base\RuntimeError.obj  ..\..\sourcebase\base\CLogger.obj  ..\..\sourcebase\base\CProbeLogger.obj  ..\..\sourcebase\base\monitorIndex.obj  ..\..\sourcebase\base\printinfo.obj 
base_lib=/libpath:..\..\sourcebase\base\ IPHLPAPI.lib
base_include= ..\..\sourcebase\base\CBaseObject.h  ..\..\sourcebase\base\BaseFunction.h  ..\..\sourcebase\base\DesignError.h  ..\..\sourcebase\base\RuntimeError.h  ..\..\sourcebase\base\CLogger.h  ..\..\sourcebase\base\CProbeLogger.h  ..\..\sourcebase\base\monitorIndex.h  ..\..\sourcebase\base\public.h  ..\..\sourcebase\base\printinfo.h 
base_includedir=-I..\..\sourcebase\base\.
utility_obj= ..\..\sourcebase\utility\CTimeMeter.obj  ..\..\sourcebase\utility\utility.obj  ..\..\sourcebase\utility\Config.obj  ..\..\sourcebase\utility\CConfig.obj  ..\..\sourcebase\utility\profile.obj  ..\..\sourcebase\utility\SGEJson.obj 
utility_include= ..\..\sourcebase\utility\CTimeMeter.h  ..\..\sourcebase\utility\utility.h  ..\..\sourcebase\utility\Config.h  ..\..\sourcebase\utility\CConfig.h  ..\..\sourcebase\utility\profile.h  ..\..\sourcebase\utility\SGEJson.h 
utility_includedir=-I..\..\sourcebase\utility\.
datastruct_obj= ..\..\sourcebase\datastruct\CFixMem.obj  ..\..\sourcebase\datastruct\CAVLTree.obj  ..\..\sourcebase\datastruct\CTransaction.obj  ..\..\sourcebase\datastruct\CMemory.obj  ..\..\sourcebase\datastruct\CFiniteState.obj  ..\..\sourcebase\datastruct\CacheList.obj  ..\..\sourcebase\datastruct\FieldDescribe.obj  ..\..\sourcebase\datastruct\FieldSet.obj  ..\..\sourcebase\datastruct\Index.obj  ..\..\sourcebase\datastruct\Package.obj  ..\..\sourcebase\datastruct\Flow.obj  ..\..\sourcebase\datastruct\ReadOnlyFlow.obj  ..\..\sourcebase\datastruct\FlowReader.obj  ..\..\sourcebase\datastruct\OrderingQ.obj  ..\..\sourcebase\datastruct\CachedFileFlow.obj  ..\..\sourcebase\datastruct\LockFileFlow.obj  ..\..\sourcebase\datastruct\CachedFlow.obj  ..\..\sourcebase\datastruct\ReqFlow.obj  ..\..\sourcebase\datastruct\FileFlow.obj  ..\..\sourcebase\datastruct\IndexPackageFlow.obj  ..\..\sourcebase\datastruct\CSVParser.obj  ..\..\sourcebase\datastruct\CSequenceInterface.obj  ..\..\sourcebase\datastruct\CMemorySequence.obj  ..\..\sourcebase\datastruct\CErrorEngine.obj  ..\..\sourcebase\datastruct\CDate.obj  ..\..\sourcebase\datastruct\Allocator.obj  ..\..\sourcebase\datastruct\CHashIndex.obj  ..\..\sourcebase\datastruct\PtrList.obj  ..\..\sourcebase\datastruct\ObjAllocator.obj  ..\..\sourcebase\datastruct\ExCachedFlow.obj 
datastruct_include= ..\..\sourcebase\datastruct\LockFileFlow.h  ..\..\sourcebase\datastruct\ReqFlow.h  ..\..\sourcebase\datastruct\CachedFileFlow.h  ..\..\sourcebase\datastruct\CachedFlow.h  ..\..\sourcebase\datastruct\IndexPackageFlow.h  ..\..\sourcebase\datastruct\FileFlow.h  ..\..\sourcebase\datastruct\CFixMem.h  ..\..\sourcebase\datastruct\CAVLTree.h  ..\..\sourcebase\datastruct\CResource.h  ..\..\sourcebase\datastruct\CTransaction.h  ..\..\sourcebase\datastruct\CMemory.h  ..\..\sourcebase\datastruct\CFiniteState.h  ..\..\sourcebase\datastruct\CacheList.h  ..\..\sourcebase\datastruct\FieldDescribe.h  ..\..\sourcebase\datastruct\FieldSet.h  ..\..\sourcebase\datastruct\Index.h  ..\..\sourcebase\datastruct\Package.h  ..\..\sourcebase\datastruct\HashMap.h  ..\..\sourcebase\datastruct\Flow.h  ..\..\sourcebase\datastruct\ReadOnlyFlow.h  ..\..\sourcebase\datastruct\FlowReader.h  ..\..\sourcebase\datastruct\PersistentState.h  ..\..\sourcebase\datastruct\OrderingQ.h  ..\..\sourcebase\datastruct\UFDataType.h  ..\..\sourcebase\datastruct\CSVParser.h  ..\..\sourcebase\datastruct\CSequenceInterface.h  ..\..\sourcebase\datastruct\CMemorySequence.h  ..\..\sourcebase\datastruct\CErrorEngine.h  ..\..\sourcebase\datastruct\CDate.h  ..\..\sourcebase\datastruct\Allocator.h  ..\..\sourcebase\datastruct\MemoryStack.h  ..\..\sourcebase\datastruct\ThreadSafeFlow.h  ..\..\sourcebase\datastruct\CHashIndex.h  ..\..\sourcebase\datastruct\PtrList.h  ..\..\sourcebase\datastruct\ObjAllocator.h  ..\..\sourcebase\datastruct\ExCachedFlow.h 
datastruct_includedir=-I..\..\sourcebase\datastruct\.
probelogger_obj= ..\..\sourcebase\probelogger\CSyslogService.obj  ..\..\sourcebase\probelogger\CFilelogService.obj 
probelogger_include= ..\..\sourcebase\probelogger\CSyslogService.h  ..\..\sourcebase\probelogger\CFilelogService.h 
probelogger_includedir=-I..\..\sourcebase\probelogger\.
xml_obj= ..\..\sourcebase\xml\CXML.obj  ..\..\sourcebase\xml\XMLAction.obj 
xml_include= ..\..\sourcebase\xml\CXML.h  ..\..\sourcebase\xml\XMLAction.h 
xml_includedir=-I..\..\sourcebase\xml\.
network_obj= ..\..\sourcebase\network\Channel.obj  ..\..\sourcebase\network\Client.obj  ..\..\sourcebase\network\ListenCtrl.obj  ..\..\sourcebase\network\NetworkFactory.obj  ..\..\sourcebase\network\Server.obj  ..\..\sourcebase\network\ServiceName.obj  ..\..\sourcebase\network\SocketInit.obj 
network_include= ..\..\sourcebase\network\Channel.h  ..\..\sourcebase\network\Client.h  ..\..\sourcebase\network\ListenCtrl.h  ..\..\sourcebase\network\NetworkFactory.h  ..\..\sourcebase\network\Server.h  ..\..\sourcebase\network\ServiceName.h  ..\..\sourcebase\network\SocketInit.h 
network_includedir=-I..\..\sourcebase\network\.
event_obj= ..\..\sourcebase\event\EventHandler.obj  ..\..\sourcebase\event\EventQueue.obj  ..\..\sourcebase\event\EventDispatcher.obj  ..\..\sourcebase\event\Reactor.obj  ..\..\sourcebase\event\Semaphore.obj  ..\..\sourcebase\event\Thread.obj  ..\..\sourcebase\event\SelectReactor.obj  ..\..\sourcebase\event\PipeEventHandler.obj  ..\..\sourcebase\event\TimerHeap.obj  ..\..\sourcebase\event\EpollReactor.obj  ..\..\sourcebase\event\SimpleReactor.obj 
event_include= ..\..\sourcebase\event\EventHandler.h  ..\..\sourcebase\event\EventQueue.h  ..\..\sourcebase\event\Reactor.h  ..\..\sourcebase\event\Semaphore.h  ..\..\sourcebase\event\Thread.h  ..\..\sourcebase\event\Mutex.h  ..\..\sourcebase\event\SelectReactor.h  ..\..\sourcebase\event\TimerHeap.h  ..\..\sourcebase\event\TimerQueue.h  ..\..\sourcebase\event\EventDispatcher.h  ..\..\sourcebase\event\EpollReactor.h  ..\..\sourcebase\event\PipeEventHandler.h  ..\..\sourcebase\event\SimpleReactor.h 
event_includedir=-I..\..\sourcebase\event\.
tcpnetwork_obj= ..\..\sourcebase\tcpnetwork\TcpChannel.obj  ..\..\sourcebase\tcpnetwork\TcpClient.obj  ..\..\sourcebase\tcpnetwork\TcpServer.obj  ..\..\sourcebase\tcpnetwork\TcpNetworkFactory.obj 
tcpnetwork_include= ..\..\sourcebase\tcpnetwork\TcpChannel.h  ..\..\sourcebase\tcpnetwork\TcpClient.h  ..\..\sourcebase\tcpnetwork\TcpServer.h  ..\..\sourcebase\tcpnetwork\TcpNetworkFactory.h 
tcpnetwork_includedir=-I..\..\sourcebase\tcpnetwork\.
mergeUFXML_obj= .\mergeUFXML.obj 
mergeUFXML_include=
mergeUFXML_includedir=-I.\.

all_objs= $(platform_obj)  $(base_obj)  $(utility_obj)  $(datastruct_obj)  $(probelogger_obj)  $(xml_obj)  $(network_obj)  $(event_obj)  $(tcpnetwork_obj)  $(mergeUFXML_obj) 
all_libs= $(platform_lib)  $(base_lib)  $(utility_lib)  $(datastruct_lib)  $(probelogger_lib)  $(xml_lib)  $(network_lib)  $(event_lib)  $(tcpnetwork_lib)  $(mergeUFXML_lib) 
INCLUDEDIR= $(platform_includedir)  $(base_includedir)  $(utility_includedir)  $(datastruct_includedir)  $(probelogger_includedir)  $(xml_includedir)  $(network_includedir)  $(event_includedir)  $(tcpnetwork_includedir)  $(mergeUFXML_includedir) 

..\..\sourcebase\platform\system.obj: ..\..\sourcebase\platform\system.cpp $(platform_include)  
..\..\sourcebase\platform\platform.obj: ..\..\sourcebase\platform\platform.cpp $(platform_include)  
..\..\sourcebase\platform\mpath.obj: ..\..\sourcebase\platform\mpath.cpp $(platform_include)  
..\..\sourcebase\base\CBaseObject.obj: ..\..\sourcebase\base\CBaseObject.cpp $(base_include)   $(platform_include)
..\..\sourcebase\base\BaseFunction.obj: ..\..\sourcebase\base\BaseFunction.cpp $(base_include)   $(platform_include)
..\..\sourcebase\base\DesignError.obj: ..\..\sourcebase\base\DesignError.cpp $(base_include)   $(platform_include)
..\..\sourcebase\base\RuntimeError.obj: ..\..\sourcebase\base\RuntimeError.cpp $(base_include)   $(platform_include)
..\..\sourcebase\base\CLogger.obj: ..\..\sourcebase\base\CLogger.cpp $(base_include)   $(platform_include)
..\..\sourcebase\base\CProbeLogger.obj: ..\..\sourcebase\base\CProbeLogger.cpp $(base_include)   $(platform_include)
..\..\sourcebase\base\monitorIndex.obj: ..\..\sourcebase\base\monitorIndex.cpp $(base_include)   $(platform_include)
..\..\sourcebase\base\printinfo.obj: ..\..\sourcebase\base\printinfo.cpp $(base_include)   $(platform_include)
..\..\sourcebase\utility\CTimeMeter.obj: ..\..\sourcebase\utility\CTimeMeter.cpp $(utility_include)   $(platform_include) $(base_include)
..\..\sourcebase\utility\utility.obj: ..\..\sourcebase\utility\utility.cpp $(utility_include)   $(platform_include) $(base_include)
..\..\sourcebase\utility\Config.obj: ..\..\sourcebase\utility\Config.cpp $(utility_include)   $(platform_include) $(base_include)
..\..\sourcebase\utility\CConfig.obj: ..\..\sourcebase\utility\CConfig.cpp $(utility_include)   $(platform_include) $(base_include)
..\..\sourcebase\utility\profile.obj: ..\..\sourcebase\utility\profile.cpp $(utility_include)   $(platform_include) $(base_include)
..\..\sourcebase\utility\SGEJson.obj: ..\..\sourcebase\utility\SGEJson.cpp $(utility_include)   $(platform_include) $(base_include)
..\..\sourcebase\datastruct\CFixMem.obj: ..\..\sourcebase\datastruct\CFixMem.cpp $(datastruct_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include)
..\..\sourcebase\datastruct\CAVLTree.obj: ..\..\sourcebase\datastruct\CAVLTree.cpp $(datastruct_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include)
..\..\sourcebase\datastruct\CTransaction.obj: ..\..\sourcebase\datastruct\CTransaction.cpp $(datastruct_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include)
..\..\sourcebase\datastruct\CMemory.obj: ..\..\sourcebase\datastruct\CMemory.cpp $(datastruct_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include)
..\..\sourcebase\datastruct\CFiniteState.obj: ..\..\sourcebase\datastruct\CFiniteState.cpp $(datastruct_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include)
..\..\sourcebase\datastruct\CacheList.obj: ..\..\sourcebase\datastruct\CacheList.cpp $(datastruct_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include)
..\..\sourcebase\datastruct\FieldDescribe.obj: ..\..\sourcebase\datastruct\FieldDescribe.cpp $(datastruct_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include)
..\..\sourcebase\datastruct\FieldSet.obj: ..\..\sourcebase\datastruct\FieldSet.cpp $(datastruct_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include)
..\..\sourcebase\datastruct\Index.obj: ..\..\sourcebase\datastruct\Index.cpp $(datastruct_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include)
..\..\sourcebase\datastruct\Package.obj: ..\..\sourcebase\datastruct\Package.cpp $(datastruct_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include)
..\..\sourcebase\datastruct\Flow.obj: ..\..\sourcebase\datastruct\Flow.cpp $(datastruct_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include)
..\..\sourcebase\datastruct\ReadOnlyFlow.obj: ..\..\sourcebase\datastruct\ReadOnlyFlow.cpp $(datastruct_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include)
..\..\sourcebase\datastruct\FlowReader.obj: ..\..\sourcebase\datastruct\FlowReader.cpp $(datastruct_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include)
..\..\sourcebase\datastruct\OrderingQ.obj: ..\..\sourcebase\datastruct\OrderingQ.cpp $(datastruct_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include)
..\..\sourcebase\datastruct\CachedFileFlow.obj: ..\..\sourcebase\datastruct\CachedFileFlow.cpp $(datastruct_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include)
..\..\sourcebase\datastruct\LockFileFlow.obj: ..\..\sourcebase\datastruct\LockFileFlow.cpp $(datastruct_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include)
..\..\sourcebase\datastruct\CachedFlow.obj: ..\..\sourcebase\datastruct\CachedFlow.cpp $(datastruct_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include)
..\..\sourcebase\datastruct\ReqFlow.obj: ..\..\sourcebase\datastruct\ReqFlow.cpp $(datastruct_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include)
..\..\sourcebase\datastruct\FileFlow.obj: ..\..\sourcebase\datastruct\FileFlow.cpp $(datastruct_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include)
..\..\sourcebase\datastruct\IndexPackageFlow.obj: ..\..\sourcebase\datastruct\IndexPackageFlow.cpp $(datastruct_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include)
..\..\sourcebase\datastruct\CSVParser.obj: ..\..\sourcebase\datastruct\CSVParser.cpp $(datastruct_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include)
..\..\sourcebase\datastruct\CSequenceInterface.obj: ..\..\sourcebase\datastruct\CSequenceInterface.cpp $(datastruct_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include)
..\..\sourcebase\datastruct\CMemorySequence.obj: ..\..\sourcebase\datastruct\CMemorySequence.cpp $(datastruct_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include)
..\..\sourcebase\datastruct\CErrorEngine.obj: ..\..\sourcebase\datastruct\CErrorEngine.cpp $(datastruct_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include)
..\..\sourcebase\datastruct\CDate.obj: ..\..\sourcebase\datastruct\CDate.cpp $(datastruct_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include)
..\..\sourcebase\datastruct\Allocator.obj: ..\..\sourcebase\datastruct\Allocator.cpp $(datastruct_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include)
..\..\sourcebase\datastruct\CHashIndex.obj: ..\..\sourcebase\datastruct\CHashIndex.cpp $(datastruct_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include)
..\..\sourcebase\datastruct\PtrList.obj: ..\..\sourcebase\datastruct\PtrList.cpp $(datastruct_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include)
..\..\sourcebase\datastruct\ObjAllocator.obj: ..\..\sourcebase\datastruct\ObjAllocator.cpp $(datastruct_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include)
..\..\sourcebase\datastruct\ExCachedFlow.obj: ..\..\sourcebase\datastruct\ExCachedFlow.cpp $(datastruct_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include)
..\..\sourcebase\probelogger\CSyslogService.obj: ..\..\sourcebase\probelogger\CSyslogService.cpp $(probelogger_include)   $(platform_include) $(base_include) $(datastruct_include)
..\..\sourcebase\probelogger\CFilelogService.obj: ..\..\sourcebase\probelogger\CFilelogService.cpp $(probelogger_include)   $(platform_include) $(base_include) $(datastruct_include)
..\..\sourcebase\xml\CXML.obj: ..\..\sourcebase\xml\CXML.cpp $(xml_include)   $(platform_include) $(base_include) $(probelogger_include) $(datastruct_include) $(utility_include)
..\..\sourcebase\xml\XMLAction.obj: ..\..\sourcebase\xml\XMLAction.cpp $(xml_include)   $(platform_include) $(base_include) $(probelogger_include) $(datastruct_include) $(utility_include)
..\..\sourcebase\network\Channel.obj: ..\..\sourcebase\network\Channel.cpp $(network_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include) $(datastruct_include) $(event_include)
..\..\sourcebase\network\Client.obj: ..\..\sourcebase\network\Client.cpp $(network_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include) $(datastruct_include) $(event_include)
..\..\sourcebase\network\ListenCtrl.obj: ..\..\sourcebase\network\ListenCtrl.cpp $(network_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include) $(datastruct_include) $(event_include)
..\..\sourcebase\network\NetworkFactory.obj: ..\..\sourcebase\network\NetworkFactory.cpp $(network_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include) $(datastruct_include) $(event_include)
..\..\sourcebase\network\Server.obj: ..\..\sourcebase\network\Server.cpp $(network_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include) $(datastruct_include) $(event_include)
..\..\sourcebase\network\ServiceName.obj: ..\..\sourcebase\network\ServiceName.cpp $(network_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include) $(datastruct_include) $(event_include)
..\..\sourcebase\network\SocketInit.obj: ..\..\sourcebase\network\SocketInit.cpp $(network_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include) $(datastruct_include) $(event_include)
..\..\sourcebase\event\EventHandler.obj: ..\..\sourcebase\event\EventHandler.cpp $(event_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include) $(datastruct_include) $(network_include)
..\..\sourcebase\event\EventQueue.obj: ..\..\sourcebase\event\EventQueue.cpp $(event_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include) $(datastruct_include) $(network_include)
..\..\sourcebase\event\EventDispatcher.obj: ..\..\sourcebase\event\EventDispatcher.cpp $(event_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include) $(datastruct_include) $(network_include)
..\..\sourcebase\event\Reactor.obj: ..\..\sourcebase\event\Reactor.cpp $(event_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include) $(datastruct_include) $(network_include)
..\..\sourcebase\event\Semaphore.obj: ..\..\sourcebase\event\Semaphore.cpp $(event_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include) $(datastruct_include) $(network_include)
..\..\sourcebase\event\Thread.obj: ..\..\sourcebase\event\Thread.cpp $(event_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include) $(datastruct_include) $(network_include)
..\..\sourcebase\event\SelectReactor.obj: ..\..\sourcebase\event\SelectReactor.cpp $(event_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include) $(datastruct_include) $(network_include)
..\..\sourcebase\event\PipeEventHandler.obj: ..\..\sourcebase\event\PipeEventHandler.cpp $(event_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include) $(datastruct_include) $(network_include)
..\..\sourcebase\event\TimerHeap.obj: ..\..\sourcebase\event\TimerHeap.cpp $(event_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include) $(datastruct_include) $(network_include)
..\..\sourcebase\event\EpollReactor.obj: ..\..\sourcebase\event\EpollReactor.cpp $(event_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include) $(datastruct_include) $(network_include)
..\..\sourcebase\event\SimpleReactor.obj: ..\..\sourcebase\event\SimpleReactor.cpp $(event_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include) $(datastruct_include) $(network_include)
..\..\sourcebase\tcpnetwork\TcpChannel.obj: ..\..\sourcebase\tcpnetwork\TcpChannel.cpp $(tcpnetwork_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include) $(datastruct_include) $(network_include) $(event_include)
..\..\sourcebase\tcpnetwork\TcpClient.obj: ..\..\sourcebase\tcpnetwork\TcpClient.cpp $(tcpnetwork_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include) $(datastruct_include) $(network_include) $(event_include)
..\..\sourcebase\tcpnetwork\TcpServer.obj: ..\..\sourcebase\tcpnetwork\TcpServer.cpp $(tcpnetwork_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include) $(datastruct_include) $(network_include) $(event_include)
..\..\sourcebase\tcpnetwork\TcpNetworkFactory.obj: ..\..\sourcebase\tcpnetwork\TcpNetworkFactory.cpp $(tcpnetwork_include)   $(platform_include) $(base_include) $(probelogger_include) $(utility_include) $(datastruct_include) $(network_include) $(event_include)
.\mergeUFXML.obj: .\mergeUFXML.cpp $(mergeUFXML_include)   $(xml_include)

copytargetall= 
pumptargetall= 

$(target): $(all_objs)
	$(LINK) $(LDFLAGS) -out:$@ $(all_objs) $(all_libs) $(LIBS) >> output


clean:
	-$(DEL) $(platform_obj)
	-$(DEL) $(base_obj)
	-$(DEL) $(utility_obj)
	-$(DEL) $(datastruct_obj)
	-$(DEL) $(probelogger_obj)
	-$(DEL) $(xml_obj)
	-$(DEL) $(network_obj)
	-$(DEL) $(event_obj)
	-$(DEL) $(tcpnetwork_obj)
	-$(DEL) $(mergeUFXML_obj)
	-$(DEL) $(copytargetall)
	-$(DEL) $(pumptargetall)
	-$(DEL) $(target)

pump: $(pumptargetall)

