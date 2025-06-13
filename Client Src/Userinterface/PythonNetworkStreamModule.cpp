//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

// Arat

PyObject* netRegisterErrorLog(PyObject* poSelf, PyObject* poArgs)
{
	char* szLog;
	if (!PyTuple_GetString(poArgs, 0, &szLog))
		return Py_BuildException();

	return Py_BuildNone();
}

// Altýna ekle


#if defined(ENABLE_SEND_TARGET_INFO)
PyObject* netRequestTargetInfo(PyObject* poSelf, PyObject* poArgs)
{
	DWORD dwVID;

	if (!PyArg_ParseTuple(poArgs, "i", &dwVID))
	{
		return Py_BuildException();
	}
	if (dwVID < 0)
	{
		return Py_BuildNone();
	}

	CPythonNetworkStream& rns = CPythonNetworkStream::Instance();
	rns.SendTargetInfoPacket(dwVID);

	return Py_BuildNone();
}
#endif


//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

// Arat

		// Log
		{ "RegisterErrorLog", netRegisterErrorLog, METH_VARARGS },

// Altýna ekle

#if defined(ENABLE_SEND_TARGET_INFO)
		{ "RequestTargetInfo", netRequestTargetInfo, METH_VARARGS },
#endif

//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################