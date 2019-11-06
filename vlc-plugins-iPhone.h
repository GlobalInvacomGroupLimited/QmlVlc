#include <stddef.h>

#ifdef __cplusplus
extern "C"{
#endif
int vlc_entry__codec_libzvbi (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_chroma_yuy2_i422 (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_chroma_yuy2_i420 (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_chroma_yuvp (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_output_yuv (int (*)(void *, void *, int, ...), void *);
int vlc_entry__misc_xml_libxml (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_xa (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_output_wextern (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_webvtt_libwebvtt (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_output_wdummy (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_wav (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_libvpx (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_output_ios (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_libvorbis (int (*)(void *, void *, int, ...), void *);
int vlc_entry__misc_rtsp (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_voc (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_vobsub (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_output_vmem (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_libvideotoolbox (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_output_splitter (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_output_vgl (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_output_vdummy (int (*)(void *, void *, int, ...), void *);
int vlc_entry__access_vdr (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_vc1 (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_uleaddvaudio (int (*)(void *, void *, int, ...), void *);
int vlc_entry__audio_filter_resampler_ugly (int (*)(void *, void *, int, ...), void *);
int vlc_entry__access_udp (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_ty (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_libtwolame (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_ttml_ttml (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_tta (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_mpeg_libts (int (*)(void *, void *, int, ...), void *);
int vlc_entry__audio_filter_channel_mixer_trivial (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_filter_transform (int (*)(void *, void *, int, ...), void *);
int vlc_entry__audio_filter_converter_tospdif (int (*)(void *, void *, int, ...), void *);
int vlc_entry__access_timecode (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_libtheora (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_textst (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_telx (int (*)(void *, void *, int, ...), void *);
int vlc_entry__text_renderer_tdummy (int (*)(void *, void *, int, ...), void *);
int vlc_entry__access_tcp (int (*)(void *, void *, int, ...), void *);
int vlc_entry__meta_engine_libtaglib (int (*)(void *, void *, int, ...), void *);
int vlc_entry__logger_syslog (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_chroma_libswscale (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_svcdsub (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_subtitle (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_subsusf (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_substx3g (int (*)(void *, void *, int, ...), void *);
int vlc_entry__spu_subsdelay (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_subsdec (int (*)(void *, void *, int, ...), void *);
int vlc_entry__stream_out_transcode_libstream_out_transcode (int (*)(void *, void *, int, ...), void *);
int vlc_entry__stream_out_libstream_out_standard (int (*)(void *, void *, int, ...), void *);
int vlc_entry__stream_out_smem (int (*)(void *, void *, int, ...), void *);
int vlc_entry__stream_out_setid (int (*)(void *, void *, int, ...), void *);
int vlc_entry__stream_out_libstream_out_rtp (int (*)(void *, void *, int, ...), void *);
int vlc_entry__stream_out_record (int (*)(void *, void *, int, ...), void *);
int vlc_entry__stream_out_gather (int (*)(void *, void *, int, ...), void *);
int vlc_entry__stream_out_es (int (*)(void *, void *, int, ...), void *);
int vlc_entry__stream_out_duplicate (int (*)(void *, void *, int, ...), void *);
int vlc_entry__stream_out_dummy (int (*)(void *, void *, int, ...), void *);
int vlc_entry__stream_out_display (int (*)(void *, void *, int, ...), void *);
int vlc_entry__stream_out_description (int (*)(void *, void *, int, ...), void *);
int vlc_entry__stream_out_delay (int (*)(void *, void *, int, ...), void *);
int vlc_entry__stream_out_cycle (int (*)(void *, void *, int, ...), void *);
int vlc_entry__stream_out_chromecast_libstream_out_chromecast (int (*)(void *, void *, int, ...), void *);
int vlc_entry__stream_out_bridge (int (*)(void *, void *, int, ...), void *);
int vlc_entry__stream_out_autodel (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_stl (int (*)(void *, void *, int, ...), void *);
int vlc_entry__audio_filter_stereo_widen (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_spudec_libspudec (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_libspeex (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_spdif (int (*)(void *, void *, int, ...), void *);
int vlc_entry__audio_filter_spatializer_spatializer (int (*)(void *, void *, int, ...), void *);
int vlc_entry__audio_filter_channel_mixer_libspatialaudio (int (*)(void *, void *, int, ...), void *);
int vlc_entry__audio_filter_resampler_libsoxr (int (*)(void *, void *, int, ...), void *);
int vlc_entry__access_libsmb2 (int (*)(void *, void *, int, ...), void *);
int vlc_entry__stream_filter_skiptags (int (*)(void *, void *, int, ...), void *);
int vlc_entry__audio_filter_channel_mixer_libsimple_channel_mixer (int (*)(void *, void *, int, ...), void *);
int vlc_entry__access_libsftp (int (*)(void *, void *, int, ...), void *);
int vlc_entry__misc_libsecuretransport (int (*)(void *, void *, int, ...), void *);
int vlc_entry__access_sdp (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_scte27 (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_scte18 (int (*)(void *, void *, int, ...), void *);
int vlc_entry__audio_filter_scaletempo (int (*)(void *, void *, int, ...), void *);
int vlc_entry__audio_filter_libscaletempo_pitch (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_filter_scale (int (*)(void *, void *, int, ...), void *);
int vlc_entry__access_satip (int (*)(void *, void *, int, ...), void *);
int vlc_entry__services_discovery_libsap (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_chroma_rv32 (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_rtpvideo (int (*)(void *, void *, int, ...), void *);
int vlc_entry__access_rtp_librtp (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_filter_rotate (int (*)(void *, void *, int, ...), void *);
int vlc_entry__access_librist (int (*)(void *, void *, int, ...), void *);
int vlc_entry__stream_filter_record (int (*)(void *, void *, int, ...), void *);
int vlc_entry__control_rc (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_rawvideo (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_rawvid (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_rawdv (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_rawaud (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_pva (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_mpeg_ps (int (*)(void *, void *, int, ...), void *);
int vlc_entry__stream_filter_prefetch (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_png (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_playlist_playlist (int (*)(void *, void *, int, ...), void *);
int vlc_entry__audio_filter_param_eq (int (*)(void *, void *, int, ...), void *);
int vlc_entry__packetizer_vc1 (int (*)(void *, void *, int, ...), void *);
int vlc_entry__packetizer_mpegvideo (int (*)(void *, void *, int, ...), void *);
int vlc_entry__packetizer_mpegaudio (int (*)(void *, void *, int, ...), void *);
int vlc_entry__packetizer_mpeg4video (int (*)(void *, void *, int, ...), void *);
int vlc_entry__packetizer_mpeg4audio (int (*)(void *, void *, int, ...), void *);
int vlc_entry__packetizer_mlp (int (*)(void *, void *, int, ...), void *);
int vlc_entry__packetizer_mjpeg (int (*)(void *, void *, int, ...), void *);
int vlc_entry__packetizer_hevc (int (*)(void *, void *, int, ...), void *);
int vlc_entry__packetizer_h264 (int (*)(void *, void *, int, ...), void *);
int vlc_entry__packetizer_flac (int (*)(void *, void *, int, ...), void *);
int vlc_entry__packetizer_dts (int (*)(void *, void *, int, ...), void *);
int vlc_entry__packetizer_copy (int (*)(void *, void *, int, ...), void *);
int vlc_entry__packetizer_libpacketizer_avparser (int (*)(void *, void *, int, ...), void *);
int vlc_entry__packetizer_av1 (int (*)(void *, void *, int, ...), void *);
int vlc_entry__packetizer_a52 (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_libopus (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_liboggspots (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_libogg (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_nuv (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_nsv (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_nsc (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_filter_noseek (int (*)(void *, void *, int, ...), void *);
int vlc_entry__audio_filter_normvol (int (*)(void *, void *, int, ...), void *);
int vlc_entry__access_libnfs (int (*)(void *, void *, int, ...), void *);
int vlc_entry__mux_wav (int (*)(void *, void *, int, ...), void *);
int vlc_entry__mux_mpeg_libmux_ts (int (*)(void *, void *, int, ...), void *);
int vlc_entry__mux_mpeg_ps (int (*)(void *, void *, int, ...), void *);
int vlc_entry__mux_libmux_ogg (int (*)(void *, void *, int, ...), void *);
int vlc_entry__mux_mpjpeg (int (*)(void *, void *, int, ...), void *);
int vlc_entry__mux_mp4_mp4 (int (*)(void *, void *, int, ...), void *);
int vlc_entry__mux_dummy (int (*)(void *, void *, int, ...), void *);
int vlc_entry__mux_avi (int (*)(void *, void *, int, ...), void *);
int vlc_entry__mux_asf (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_mpeg_mpgv (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_libmpg123 (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_mp4_mp4 (int (*)(void *, void *, int, ...), void *);
int vlc_entry__audio_filter_channel_mixer_mono (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_libmod (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_mkv_libmkv (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_mjpeg (int (*)(void *, void *, int, ...), void *);
int vlc_entry__services_discovery_libmicrodns (int (*)(void *, void *, int, ...), void *);
int vlc_entry__keystore_memory (int (*)(void *, void *, int, ...), void *);
int vlc_entry__spu_marq (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_lpcm (int (*)(void *, void *, int, ...), void *);
int vlc_entry__spu_logo (int (*)(void *, void *, int, ...), void *);
int vlc_entry__access_liblive555 (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_liblibass (int (*)(void *, void *, int, ...), void *);
int vlc_entry__keystore_libkeychain (int (*)(void *, void *, int, ...), void *);
int vlc_entry__audio_filter_karaoke (int (*)(void *, void *, int, ...), void *);
int vlc_entry__audio_mixer_libinteger_mixer (int (*)(void *, void *, int, ...), void *);
int vlc_entry__stream_filter_inflate (int (*)(void *, void *, int, ...), void *);
int vlc_entry__access_imem_access (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_image (int (*)(void *, void *, int, ...), void *);
int vlc_entry__access_idummy (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_chroma_libi422_yuy2 (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_chroma_i422_i420 (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_chroma_libi420_yuy2 (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_chroma_i420_rgb (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_chroma_libi420_nv12 (int (*)(void *, void *, int, ...), void *);
int vlc_entry__access_http_access (int (*)(void *, void *, int, ...), void *);
int vlc_entry__access_http (int (*)(void *, void *, int, ...), void *);
int vlc_entry__stream_filter_hds_libhds (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_mpeg_h26x (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_chroma_grey_yuv (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_output_opengl_libgles2 (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_output_opengl_libglconv_cvpx (int (*)(void *, void *, int, ...), void *);
int vlc_entry__audio_filter_gain (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_g711 (int (*)(void *, void *, int, ...), void *);
int vlc_entry__access_ftp (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_filter_freeze (int (*)(void *, void *, int, ...), void *);
int vlc_entry__text_renderer_freetype_libfreetype (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_filter_fps (int (*)(void *, void *, int, ...), void *);
int vlc_entry__meta_engine_folder (int (*)(void *, void *, int, ...), void *);
int vlc_entry__audio_mixer_libfloat_mixer (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_output_flaschen (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_libflacsys (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_libflac (int (*)(void *, void *, int, ...), void *);
int vlc_entry__access_libfilesystem (int (*)(void *, void *, int, ...), void *);
int vlc_entry__logger_file (int (*)(void *, void *, int, ...), void *);
int vlc_entry__keystore_file (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_mpeg_es (int (*)(void *, void *, int, ...), void *);
int vlc_entry__audio_filter_equalizer (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_edummy (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_filter_edgedetection (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_dvbsub (int (*)(void *, void *, int, ...), void *);
int vlc_entry__control_dummy (int (*)(void *, void *, int, ...), void *);
int vlc_entry__audio_filter_channel_mixer_dolby (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_directory (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_libdemux_stl (int (*)(void *, void *, int, ...), void *);
int vlc_entry__stream_out_chromecast_libdemux_chromecast (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_libdemux_cdg (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_filter_deinterlace_libdeinterlace (int (*)(void *, void *, int, ...), void *);
int vlc_entry__stream_filter_decomp (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_ddummy (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_libdav1d (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_chroma_libcvpx (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_cvdsub (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_filter_croppadd (int (*)(void *, void *, int, ...), void *);
int vlc_entry__logger_console (int (*)(void *, void *, int, ...), void *);
int vlc_entry__audio_filter_compressor (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_filter_ci_filters (int (*)(void *, void *, int, ...), void *);
int vlc_entry__audio_filter_chorus_flanger (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_chroma_chain (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_cdg (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_cc (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_filter_canvas (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_caf (int (*)(void *, void *, int, ...), void *);
int vlc_entry__stream_filter_cache_read (int (*)(void *, void *, int, ...), void *);
int vlc_entry__stream_filter_cache_block (int (*)(void *, void *, int, ...), void *);
int vlc_entry__services_discovery_libbonjour (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_filter_blend (int (*)(void *, void *, int, ...), void *);
int vlc_entry__access_libavio (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_avi_avi (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_avformat_libavformat (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_avcodec_libavcodec (int (*)(void *, void *, int, ...), void *);
int vlc_entry__audio_output_audiounit_ios (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_audiotoolbox_midi (int (*)(void *, void *, int, ...), void *);
int vlc_entry__audio_filter_converter_libaudio_format (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_au (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_asf_asf (int (*)(void *, void *, int, ...), void *);
int vlc_entry__stream_extractor_libarchive (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_araw (int (*)(void *, void *, int, ...), void *);
int vlc_entry__access_amt (int (*)(void *, void *, int, ...), void *);
int vlc_entry__audio_output_amem (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_aiff (int (*)(void *, void *, int, ...), void *);
int vlc_entry__audio_output_libafile (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_aes3 (int (*)(void *, void *, int, ...), void *);
int vlc_entry__audio_output_adummy (int (*)(void *, void *, int, ...), void *);
int vlc_entry__codec_adpcm (int (*)(void *, void *, int, ...), void *);
int vlc_entry__video_filter_adjust (int (*)(void *, void *, int, ...), void *);
int vlc_entry__stream_filter_adf (int (*)(void *, void *, int, ...), void *);
int vlc_entry__demux_adaptive_libadaptive (int (*)(void *, void *, int, ...), void *);
int vlc_entry__access_output_libaccess_output_shout (int (*)(void *, void *, int, ...), void *);
int vlc_entry__access_output_libaccess_output_rist (int (*)(void *, void *, int, ...), void *);
int vlc_entry__access_output_http (int (*)(void *, void *, int, ...), void *);
int vlc_entry__access_output_file (int (*)(void *, void *, int, ...), void *);
int vlc_entry__access_output_dummy (int (*)(void *, void *, int, ...), void *);
int vlc_entry__access_mms_libaccess_mms (int (*)(void *, void *, int, ...), void *);
int vlc_entry__access_concat (int (*)(void *, void *, int, ...), void *);
#ifdef __cplusplus
}
#endif


#ifdef __arm__
#endif

const void *vlc_static_modules[] = {
(void *)  vlc_entry__codec_libzvbi,
(void *)  vlc_entry__video_chroma_yuy2_i422,
(void *)  vlc_entry__video_chroma_yuy2_i420,
(void *)  vlc_entry__video_chroma_yuvp,
(void *)  vlc_entry__video_output_yuv,
(void *)  vlc_entry__misc_xml_libxml,
(void *)  vlc_entry__demux_xa,
(void *)  vlc_entry__video_output_wextern,
(void *)  vlc_entry__codec_webvtt_libwebvtt,
(void *)  vlc_entry__video_output_wdummy,
(void *)  vlc_entry__demux_wav,
(void *)  vlc_entry__codec_libvpx,
(void *)  vlc_entry__video_output_ios,
(void *)  vlc_entry__codec_libvorbis,
(void *)  vlc_entry__misc_rtsp,
(void *)  vlc_entry__demux_voc,
(void *)  vlc_entry__demux_vobsub,
(void *)  vlc_entry__video_output_vmem,
(void *)  vlc_entry__codec_libvideotoolbox,
(void *)  vlc_entry__video_output_splitter,
(void *)  vlc_entry__video_output_vgl,
(void *)  vlc_entry__video_output_vdummy,
(void *)  vlc_entry__access_vdr,
(void *)  vlc_entry__demux_vc1,
(void *)  vlc_entry__codec_uleaddvaudio,
(void *)  vlc_entry__audio_filter_resampler_ugly,
(void *)  vlc_entry__access_udp,
(void *)  vlc_entry__demux_ty,
(void *)  vlc_entry__codec_libtwolame,
(void *)  vlc_entry__codec_ttml_ttml,
(void *)  vlc_entry__demux_tta,
(void *)  vlc_entry__demux_mpeg_libts,
(void *)  vlc_entry__audio_filter_channel_mixer_trivial,
(void *)  vlc_entry__video_filter_transform,
(void *)  vlc_entry__audio_filter_converter_tospdif,
(void *)  vlc_entry__access_timecode,
(void *)  vlc_entry__codec_libtheora,
(void *)  vlc_entry__codec_textst,
(void *)  vlc_entry__codec_telx,
(void *)  vlc_entry__text_renderer_tdummy,
(void *)  vlc_entry__access_tcp,
(void *)  vlc_entry__meta_engine_libtaglib,
(void *)  vlc_entry__logger_syslog,
(void *)  vlc_entry__video_chroma_libswscale,
(void *)  vlc_entry__codec_svcdsub,
(void *)  vlc_entry__demux_subtitle,
(void *)  vlc_entry__codec_subsusf,
(void *)  vlc_entry__codec_substx3g,
(void *)  vlc_entry__spu_subsdelay,
(void *)  vlc_entry__codec_subsdec,
(void *)  vlc_entry__stream_out_transcode_libstream_out_transcode,
(void *)  vlc_entry__stream_out_libstream_out_standard,
(void *)  vlc_entry__stream_out_smem,
(void *)  vlc_entry__stream_out_setid,
(void *)  vlc_entry__stream_out_libstream_out_rtp,
(void *)  vlc_entry__stream_out_record,
(void *)  vlc_entry__stream_out_gather,
(void *)  vlc_entry__stream_out_es,
(void *)  vlc_entry__stream_out_duplicate,
(void *)  vlc_entry__stream_out_dummy,
(void *)  vlc_entry__stream_out_display,
(void *)  vlc_entry__stream_out_description,
(void *)  vlc_entry__stream_out_delay,
(void *)  vlc_entry__stream_out_cycle,
(void *)  vlc_entry__stream_out_chromecast_libstream_out_chromecast,
(void *)  vlc_entry__stream_out_bridge,
(void *)  vlc_entry__stream_out_autodel,
(void *)  vlc_entry__codec_stl,
(void *)  vlc_entry__audio_filter_stereo_widen,
(void *)  vlc_entry__codec_spudec_libspudec,
(void *)  vlc_entry__codec_libspeex,
(void *)  vlc_entry__codec_spdif,
(void *)  vlc_entry__audio_filter_spatializer_spatializer,
(void *)  vlc_entry__audio_filter_channel_mixer_libspatialaudio,
(void *)  vlc_entry__audio_filter_resampler_libsoxr,
(void *)  vlc_entry__access_libsmb2,
(void *)  vlc_entry__stream_filter_skiptags,
(void *)  vlc_entry__audio_filter_channel_mixer_libsimple_channel_mixer,
(void *)  vlc_entry__access_libsftp,
(void *)  vlc_entry__misc_libsecuretransport,
(void *)  vlc_entry__access_sdp,
(void *)  vlc_entry__codec_scte27,
(void *)  vlc_entry__codec_scte18,
(void *)  vlc_entry__audio_filter_scaletempo,
(void *)  vlc_entry__audio_filter_libscaletempo_pitch,
(void *)  vlc_entry__video_filter_scale,
(void *)  vlc_entry__access_satip,
(void *)  vlc_entry__services_discovery_libsap,
(void *)  vlc_entry__video_chroma_rv32,
(void *)  vlc_entry__codec_rtpvideo,
(void *)  vlc_entry__access_rtp_librtp,
(void *)  vlc_entry__video_filter_rotate,
(void *)  vlc_entry__access_librist,
(void *)  vlc_entry__stream_filter_record,
(void *)  vlc_entry__control_rc,
(void *)  vlc_entry__codec_rawvideo,
(void *)  vlc_entry__demux_rawvid,
(void *)  vlc_entry__demux_rawdv,
(void *)  vlc_entry__demux_rawaud,
(void *)  vlc_entry__demux_pva,
(void *)  vlc_entry__demux_mpeg_ps,
(void *)  vlc_entry__stream_filter_prefetch,
(void *)  vlc_entry__codec_png,
(void *)  vlc_entry__demux_playlist_playlist,
(void *)  vlc_entry__audio_filter_param_eq,
(void *)  vlc_entry__packetizer_vc1,
(void *)  vlc_entry__packetizer_mpegvideo,
(void *)  vlc_entry__packetizer_mpegaudio,
(void *)  vlc_entry__packetizer_mpeg4video,
(void *)  vlc_entry__packetizer_mpeg4audio,
(void *)  vlc_entry__packetizer_mlp,
(void *)  vlc_entry__packetizer_mjpeg,
(void *)  vlc_entry__packetizer_hevc,
(void *)  vlc_entry__packetizer_h264,
(void *)  vlc_entry__packetizer_flac,
(void *)  vlc_entry__packetizer_dts,
(void *)  vlc_entry__packetizer_copy,
(void *)  vlc_entry__packetizer_libpacketizer_avparser,
(void *)  vlc_entry__packetizer_av1,
(void *)  vlc_entry__packetizer_a52,
(void *)  vlc_entry__codec_libopus,
(void *)  vlc_entry__codec_liboggspots,
(void *)  vlc_entry__demux_libogg,
(void *)  vlc_entry__demux_nuv,
(void *)  vlc_entry__demux_nsv,
(void *)  vlc_entry__demux_nsc,
(void *)  vlc_entry__demux_filter_noseek,
(void *)  vlc_entry__audio_filter_normvol,
(void *)  vlc_entry__access_libnfs,
(void *)  vlc_entry__mux_wav,
(void *)  vlc_entry__mux_mpeg_libmux_ts,
(void *)  vlc_entry__mux_mpeg_ps,
(void *)  vlc_entry__mux_libmux_ogg,
(void *)  vlc_entry__mux_mpjpeg,
(void *)  vlc_entry__mux_mp4_mp4,
(void *)  vlc_entry__mux_dummy,
(void *)  vlc_entry__mux_avi,
(void *)  vlc_entry__mux_asf,
(void *)  vlc_entry__demux_mpeg_mpgv,
(void *)  vlc_entry__codec_libmpg123,
(void *)  vlc_entry__demux_mp4_mp4,
(void *)  vlc_entry__audio_filter_channel_mixer_mono,
(void *)  vlc_entry__demux_libmod,
(void *)  vlc_entry__demux_mkv_libmkv,
(void *)  vlc_entry__demux_mjpeg,
(void *)  vlc_entry__services_discovery_libmicrodns,
(void *)  vlc_entry__keystore_memory,
(void *)  vlc_entry__spu_marq,
(void *)  vlc_entry__codec_lpcm,
(void *)  vlc_entry__spu_logo,
(void *)  vlc_entry__access_liblive555,
(void *)  vlc_entry__codec_liblibass,
(void *)  vlc_entry__keystore_libkeychain,
(void *)  vlc_entry__audio_filter_karaoke,
(void *)  vlc_entry__audio_mixer_libinteger_mixer,
(void *)  vlc_entry__stream_filter_inflate,
(void *)  vlc_entry__access_imem_access,
(void *)  vlc_entry__demux_image,
(void *)  vlc_entry__access_idummy,
(void *)  vlc_entry__video_chroma_libi422_yuy2,
(void *)  vlc_entry__video_chroma_i422_i420,
(void *)  vlc_entry__video_chroma_libi420_yuy2,
(void *)  vlc_entry__video_chroma_i420_rgb,
(void *)  vlc_entry__video_chroma_libi420_nv12,
(void *)  vlc_entry__access_http_access,
(void *)  vlc_entry__access_http,
(void *)  vlc_entry__stream_filter_hds_libhds,
(void *)  vlc_entry__demux_mpeg_h26x,
(void *)  vlc_entry__video_chroma_grey_yuv,
(void *)  vlc_entry__video_output_opengl_libgles2,
(void *)  vlc_entry__video_output_opengl_libglconv_cvpx,
(void *)  vlc_entry__audio_filter_gain,
(void *)  vlc_entry__codec_g711,
(void *)  vlc_entry__access_ftp,
(void *)  vlc_entry__video_filter_freeze,
(void *)  vlc_entry__text_renderer_freetype_libfreetype,
(void *)  vlc_entry__video_filter_fps,
(void *)  vlc_entry__meta_engine_folder,
(void *)  vlc_entry__audio_mixer_libfloat_mixer,
(void *)  vlc_entry__video_output_flaschen,
(void *)  vlc_entry__demux_libflacsys,
(void *)  vlc_entry__codec_libflac,
(void *)  vlc_entry__access_libfilesystem,
(void *)  vlc_entry__logger_file,
(void *)  vlc_entry__keystore_file,
(void *)  vlc_entry__demux_mpeg_es,
(void *)  vlc_entry__audio_filter_equalizer,
(void *)  vlc_entry__codec_edummy,
(void *)  vlc_entry__video_filter_edgedetection,
(void *)  vlc_entry__codec_dvbsub,
(void *)  vlc_entry__control_dummy,
(void *)  vlc_entry__audio_filter_channel_mixer_dolby,
(void *)  vlc_entry__demux_directory,
(void *)  vlc_entry__demux_libdemux_stl,
(void *)  vlc_entry__stream_out_chromecast_libdemux_chromecast,
(void *)  vlc_entry__demux_libdemux_cdg,
(void *)  vlc_entry__video_filter_deinterlace_libdeinterlace,
(void *)  vlc_entry__stream_filter_decomp,
(void *)  vlc_entry__codec_ddummy,
(void *)  vlc_entry__codec_libdav1d,
(void *)  vlc_entry__video_chroma_libcvpx,
(void *)  vlc_entry__codec_cvdsub,
(void *)  vlc_entry__video_filter_croppadd,
(void *)  vlc_entry__logger_console,
(void *)  vlc_entry__audio_filter_compressor,
(void *)  vlc_entry__video_filter_ci_filters,
(void *)  vlc_entry__audio_filter_chorus_flanger,
(void *)  vlc_entry__video_chroma_chain,
(void *)  vlc_entry__codec_cdg,
(void *)  vlc_entry__codec_cc,
(void *)  vlc_entry__video_filter_canvas,
(void *)  vlc_entry__demux_caf,
(void *)  vlc_entry__stream_filter_cache_read,
(void *)  vlc_entry__stream_filter_cache_block,
(void *)  vlc_entry__services_discovery_libbonjour,
(void *)  vlc_entry__video_filter_blend,
(void *)  vlc_entry__access_libavio,
(void *)  vlc_entry__demux_avi_avi,
(void *)  vlc_entry__demux_avformat_libavformat,
(void *)  vlc_entry__codec_avcodec_libavcodec,
(void *)  vlc_entry__audio_output_audiounit_ios,
(void *)  vlc_entry__codec_audiotoolbox_midi,
(void *)  vlc_entry__audio_filter_converter_libaudio_format,
(void *)  vlc_entry__demux_au,
(void *)  vlc_entry__demux_asf_asf,
(void *)  vlc_entry__stream_extractor_libarchive,
(void *)  vlc_entry__codec_araw,
(void *)  vlc_entry__access_amt,
(void *)  vlc_entry__audio_output_amem,
(void *)  vlc_entry__demux_aiff,
(void *)  vlc_entry__audio_output_libafile,
(void *)  vlc_entry__codec_aes3,
(void *)  vlc_entry__audio_output_adummy,
(void *)  vlc_entry__codec_adpcm,
(void *)  vlc_entry__video_filter_adjust,
(void *)  vlc_entry__stream_filter_adf,
(void *)  vlc_entry__demux_adaptive_libadaptive,
(void *)  vlc_entry__access_output_libaccess_output_shout,
(void *)  vlc_entry__access_output_libaccess_output_rist,
(void *)  vlc_entry__access_output_http,
(void *)  vlc_entry__access_output_file,
(void *)  vlc_entry__access_output_dummy,
(void *)  vlc_entry__access_mms_libaccess_mms,
(void *)  vlc_entry__access_concat,
NULL
};
