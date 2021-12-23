#include <random>
#include <iostream>
using namespace std;

int main() {
    uniform_int_distribution<unsigned> u(0,9);
    default_random_engine e;    // 生成无符号随机整数
    for (size_t i =0;i<10; i++)
        // 将 u 作为随机数源
        // 每个调用返回在指定范围内并服从均匀分布的值
        cout<<u(e)<<" ";
    cout<< endl;
}

<event ID="CNN_ENG_20030630_085848.18-EV1" TYPE="Movement" SUBTYPE="Transport" MODALITY="Asserted" POLARITY="Positive" GENERICITY="Specific" TENSE="Past">
  <event_argument REFID="CNN_ENG_20030630_085848.18-E2" ROLE="Artifact"/>
  <event_argument REFID="CNN_ENG_20030630_085848.18-E3" ROLE="Origin"/>
  <event_mention ID="CNN_ENG_20030630_085848.18-EV1-1">
    <extent>
      <charseq START="93" END="134">forced hundreds of people from their homes</charseq>
    </extent>
    <ldc_scope>
      <charseq START="68" END="134">a wildfire in california forced hundreds of people from their homes</charseq>
    </ldc_scope>
    <anchor>
      <charseq START="93" END="98">forced</charseq>
    </anchor>
    <event_mention_argument REFID="CNN_ENG_20030630_085848.18-E2-2" ROLE="Artifact">
      <extent>
        <charseq START="100" END="117">hundreds of people</charseq>
      </extent>
    </event_mention_argument>
    <event_mention_argument REFID="CNN_ENG_20030630_085848.18-E3-4" ROLE="Origin">
      <extent>
        <charseq START="124" END="134">their homes</charseq>
      </extent>
    </event_mention_argument>
  </event_mention>
</event>

          "start": 20,
          "end": 21
        },
        "entity_id": "APW_ENG_20030325.0786-E26-40",
        "start": 20,
        "end": 21
      }
    ],
    "golden-event-mentions": [
      {
        "trigger": {
          "text": "retirement",
          "start": 17,
          "end": 18
        },
        "arguments": [
          {
            "role": "Person",
            "entity-type": "PER:Individual",
            "text": "Welch",
            "start": 11,
            "end": 12
          },
          {
            "role": "Entity",
            "entity-type": "ORG:Commercial",
            "text": "GE",
            "start": 20,
            "end": 21
          }
        ],
        "event_type": "Personnel:End-Position"
      }
    ],