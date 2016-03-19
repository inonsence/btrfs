class Factory : public IClassFactory {
public:
    Factory() {
        refcount = 0;
    }

    virtual ~Factory() {
    }

    // IUnknown
    
    HRESULT __stdcall QueryInterface(REFIID riid, void **ppObj);
    
    ULONG __stdcall AddRef() {
        return InterlockedIncrement(&refcount);
    }

    ULONG __stdcall Release() {
        LONG rc = InterlockedDecrement(&refcount);
        
        if (rc == 0)
            delete this;
        
        return rc;
    }

    // IClassFactory
    
    virtual HRESULT __stdcall CreateInstance(IUnknown* pUnknownOuter, const IID& iid, void** ppv);
    virtual HRESULT __stdcall LockServer(BOOL bLock);

private:
    LONG refcount;
};
