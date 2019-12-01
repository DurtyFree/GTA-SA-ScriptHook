#pragma once
#if PLEASE_DO_NOT_USE
#include <mscoree.h>
#include "Log.h"
#include "ScriptDomain.h"
#if defined ( Yield ) 
#undef Yield 
// namespace fibers
#endif 
#define CORHOST

namespace Fibers
{
   typedef    System::Runtime::InteropServices::GCHandle GCHandle;
   VOID CALLBACK unmanaged_fiberproc( PVOID pvoid );
   private ref struct StopFiber{};

   enum FiberStateEnum
   {
      FiberCreated, FiberRunning, FiberStopPending, FiberStopped
   };


#pragma unmanaged 
#if defined ( CORHOST ) 
   ICorRuntimeHost * corhost;
   void initialize_corhost()
   {
      CorBindToCurrentRuntime( 0, CLSID_CorRuntimeHost, IID_ICorRuntimeHost, (void **) &corhost );
   }


#endif 
   void CorSwitchToFiber( void * fiber )
   {

#if defined ( CORHOST ) 
      DWORD * cookie;
      corhost->SwitchOutLogicalThreadState(  &cookie );

#endif 
      SwitchToFiber( fiber );

#if defined ( CORHOST ) 
      corhost->SwitchInLogicalThreadState( cookie );

#endif 
   }


#pragma managed 
   delegate System::Object^ Coroutine();
   public ref class Fiber: public System::IDisposable
   {
   public:

#if defined ( CORHOST ) 
      static Fiber()
      {
         initialize_corhost();
      }

// namespace fibers
#endif 
      Fiber()
         : retval( 0 ), state( FiberCreated )
      {
		 void * objptr = (void *)((IntPtr)GCHandle::Alloc(this));
         fiber = CreateFiber( 0, unmanaged_fiberproc, objptr );
      }


      property bool IsRunning 
      {
         bool get()
         {
            return state != FiberStopped;
         }

      }
      static operator Coroutine^ ( Fiber^ obj )
      {
         return gcnew Coroutine( obj, &Fiber::Resume );
      }

      System::Object^ Resume()
      {
         if (  !fiber || state == FiberStopped )
                  return nullptr;

         initialize_thread();
         void * current = GetCurrentFiber();
         if ( fiber == current )
                  return nullptr;

         previousfiber = current;
         CorSwitchToFiber( fiber );
         return retval;
      }

      ~Fiber()
      {
         if ( fiber )
         {
            if ( state == FiberRunning )
            {
               initialize_thread();
               void * current = GetCurrentFiber();
               if ( fiber == current )
                              return;
               previousfiber = current;
               state = FiberStopPending;
               CorSwitchToFiber( fiber );
            }
            else
            if ( state == FiberCreated )
            {
               state = FiberStopped;
            }
            DeleteFiber( fiber );
            fiber = 0;
         }
      }

	  Action^ Run;
      //virtual void Run() = 0;
      void Yield()
      {
         CorSwitchToFiber( previousfiber );
         if ( state == FiberStopPending )
                  throw gcnew StopFiber;
      }

	        FiberStateEnum state;

   private:

      [System::ThreadStatic]
      static bool thread_is_fiber;
      void * fiber;
      void * previousfiber;
      System::Object^ retval;
      static void initialize_thread()
      {
         if (  !thread_is_fiber )
         {
            ConvertThreadToFiber( 0 );
            thread_is_fiber = true;
         }
      }


   internal:
      void * main()
      {
         state = FiberRunning;
         try
         {
            Run();
         }
         catch ( System::Object^ x ) 
         {
            System::Console::Error->WriteLine( L"\nFIBERS.DLL: main Caught {0}", x );
			//GTA::Log::Error(x->ToString());
         }

         state = FiberStopped;
         retval = nullptr;
         return previousfiber;
      }

   };

   ref class FiberMainWrapper : public MarshalByRefObject {
   public:
virtual Object^ InitializeLifetimeService() override {
			return nullptr;
		}

		void* crossfibermain( void * objptr )
		{
		  System::IntPtr ptr = (System::IntPtr)objptr;
		  GCHandle g = (GCHandle)ptr;
		  Fiber^ fiber = static_cast<Fiber^>(g.Target);
		  g.Free();
		  return fiber->main();
		}
   };

   void * fibermain( void * objptr )
   {
	   if (AppDomain::CurrentDomain->FriendlyName != "GTAScriptHook") {
		FiberMainWrapper^ wrapper = (FiberMainWrapper^)GTA::ScriptDomain::_scriptDomain->CreateInstanceAndUnwrap(Reflection::Assembly::GetAssembly(FiberMainWrapper::typeid)->FullName, FiberMainWrapper::typeid->FullName);
		return wrapper->crossfibermain(objptr);
	   } else {
		FiberMainWrapper^ wrapper = gcnew FiberMainWrapper();
		return wrapper->crossfibermain(objptr);
	   }
   }


#pragma unmanaged 
   VOID CALLBACK unmanaged_fiberproc( PVOID objptr )
   {

#if defined ( CORHOST ) 
      corhost->CreateLogicalThreadState();

#endif 
      void * previousfiber = fibermain( objptr );

#if defined ( CORHOST ) 
      corhost->DeleteLogicalThreadState();

#endif 
      SwitchToFiber( previousfiber );
   }
#pragma managed

}

// namespace fibers

#endif