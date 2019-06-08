#pragma once

#include "EncoderContext.h"
#include "ExportInfo.h"
#include "lavf.h"
#include <wx/wx.h>
#include <wx/filename.h>

class EncoderEngine
{
public:
	EncoderEngine(ExportInfo encoderInfo);
	~EncoderEngine();
	int open();
	void close();
	void finalize();
	void flushContext(EncoderContext *encoderContext);
	int writeVideoFrame(AVFrame *frame);
	int writeAudioFrame(AVFrame *frame);
	int getAudioFrameSize();
	AVMediaType getNextFrameType();
	int pass = 1;

private:
	AVPacket *packet;
	ExportInfo exportInfo;
	AVFormatContext *formatContext;
	EncoderContext videoContext;
	EncoderContext audioContext;
	int createCodecContext(const wxString codecId, EncoderContext *encoderContext, int flags);
	int encodeAndWriteFrame(EncoderContext *context, AVFrame *frame);
	int getCodecFlags(const AVMediaType type);
	int openCodec(const wxString codecId, const wxString codecOptions, EncoderContext *encoderContext, const int flags);
	int sendFrame(AVCodecContext *context, AVStream *stream, AVFrame *frame);
	int receivePackets(AVCodecContext *context, AVStream *stream);
	int audioFrameSize;
	wxString passLogFile;
};
