# 파이썬 분석 코드 파일 
import pandas as pd
import matplotlib.pyplot as plt
import gradio as gr

class App():
    def __init__(self, data, debug_log):
        debug_log.append("[DEBUG] App 객체 생성 중...")
        self.data = data
        debug_log.append("[DEBUG] 데이터가 성공적으로 저장되었습니다.")

    def data_processing(self, debug_log):
        debug_log.append("[DEBUG] 데이터 전처리 시작...")
        df = self.data[['Label', 'RSSI', 'SNR']]
        debug_log.append(f"[DEBUG] 전처리된 데이터프레임 (상위 5개):\n{df.head().to_string()}")
        return df

    def data_visualization_line(self, df, debug_log):
        debug_log.append("[DEBUG] 선 그래프 시각화 시작...")

        fig, ax1 = plt.subplots(figsize=(10, 6))
        debug_log.append("[DEBUG] 첫 번째 축 생성 완료.")

        line1, = ax1.plot(df['Label'], df['RSSI'], color='blue', marker='o', label='RSSI')
        ax1.set_ylabel('RSSI', color='blue')
        ax1.tick_params(axis='y', labelcolor='blue')
        debug_log.append("[DEBUG] RSSI 라인 플롯 완료.")

        ax2 = ax1.twinx()
        line2, = ax2.plot(df['Label'], df['SNR'], color='red', marker='x', label='SNR')
        ax2.set_ylabel('SNR', color='red')
        ax2.tick_params(axis='y', labelcolor='red')
        debug_log.append("[DEBUG] SNR 라인 플롯 완료.")

        lines = [line1, line2]
        labels = [line.get_label() for line in lines]
        ax1.legend(lines, labels, loc='upper right')

        plt.grid()
        plt.title('RSSI와 SNR의 변화율 그래프')
        fig.tight_layout()
        debug_log.append("[DEBUG] 시각화 완료 및 Figure 반환.")
        return fig

    def data_visualization_hist(self, df, debug_log):
        debug_log.append("[DEBUG] 히스토그램 시각화 시작...")

        fig, ax = plt.subplots(figsize=(10, 6))
        df[['RSSI', 'SNR']].hist(ax=ax, bins=15)
        plt.title('RSSI & SNR 히스토그램')
        plt.tight_layout()
        debug_log.append("[DEBUG] 히스토그램 시각화 완료 및 Figure 반환.")
        return fig

def main(file_path, plot_type='line'):
    debug_log = []

    try:
        debug_log.append("[DEBUG] 파일을 읽는 중...")
        data = pd.read_csv(file_path.name if hasattr(file_path, 'name') else file_path)
        debug_log.append(f"[DEBUG] 읽은 데이터 샘플:\n{data.head().to_string()}")

        app = App(data, debug_log)
        df = app.data_processing(debug_log)

        if plot_type == 'histogram':
            fig = app.data_visualization_hist(df, debug_log)
        else:
            fig = app.data_visualization_line(df, debug_log)

        return fig, df, debug_log[-1] if debug_log else ""

    except Exception as e:
        return None, None, f"[ERROR] {str(e)}"

import gradio as gr

demo = gr.Interface(
    fn=main,
    inputs=[
        gr.File(label="Upload CSV File", file_types=['.csv']),
        gr.Radio(['line', 'histogram'], label="Select Plot Type", value='line')
    ],
    outputs=[
        gr.Plot(label="Graph Output"),
        gr.DataFrame(label="Processed DataFrame"),
        gr.Textbox(label="Debug Log", lines=5, interactive=False),
    ],
    title="Signal Quality Analysis Tool",
    description="Upload a CSV file containing Label, RSSI, and SNR columns.",
    theme="compact",
)

if __name__ == "__main__":
    demo.launch()
