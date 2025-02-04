#ifndef APLAYER_H
#define APLAYER_H

#include <QObject>
#include <QFile>
#include <QAudioOutput>

class aPlayer : public QObject
{
    Q_OBJECT
public:

    typedef enum {          // 循环模式
        singleCycle,        // 单曲循环
        loopPlayback,       // 列表循环
        orderPlay           // 顺序播放
    }e_loopPattern;

    typedef enum {          // 播放状态
        playing,            // 播放中
        pause,              // 暂停中
        stopped             // 停止
    }e_playStatus;

    typedef enum {
        cmdPlayStart,       // 开始播放
        cmdPlayStop,        // 停止播放
        cmdSetLoopPattern,  // 设置循环模式
        cmdSetVolume,       // 设置音量
    }e_cmd;

    explicit aPlayer(QObject *parent = nullptr);

    bool addAudio(QString audioName, QString& error);
    void clearPlayList();
    bool playStart(QString& error);
    bool playStop(QString& error);
    QStringList getPlayList();
    int getPlayListNumber();
    void playIndex(int index, int times);
    void setLoopPattern(e_loopPattern loopPattern);
    QString getLoopPattern();
    void setLoop(int loop);
    void setVolume(int volume);
    void waitForCmd();

private:
    void init();

signals:

public slots:
    void slotPlayStart();
    void slotPlayStop();
    void slotPlayIndex(int index, int times);
    void slotClearPlayListp();
    void slotNormalCmd(e_cmd, QStringList args);   // 普通命令，无需排队
    void slotListCmd(e_cmd, QStringList args);     // 队列命令，按顺序执行

private:
    QStringList m_playList;             // 播放列表
    int m_playListIndex;                // 播放列表下标
    e_loopPattern m_lastLoopPattern;    // 上一次的循环模式
    e_loopPattern m_loopPattern;        // 循环模式
    e_playStatus m_playStatu;           // 播放状态
    QFile m_audioFile;                  // 音频输出的文件流
    QAudioDeviceInfo m_audioDeviceInfo; // 音频输出设备的信息
    QAudioFormat m_format;              // 音频输出的格式
    QAudioOutput* m_audioOutput         // 音频输出设备
        = nullptr;
    int m_currLoopTimes                 // 当前循环次数
        = 0;
    int m_loopTimes                     // 循环次数
        = -1;
};

#endif // APLAYER_H
